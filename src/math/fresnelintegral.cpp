#include "fresnelintegral.h"
#include "MathConstants.h"
#include <string>

/*!
 * FresnelIntegralĬ�Ϲ�����
 */
FresnelIntegral::FresnelIntegral()
{
}



/*!
 * FresnelIntegral ������������
 * \param x �Ǹ������������������ֵı߽�
*/
FresnelIntegral::FresnelIntegral(const std::complex<double> &p_x)
{
    m_x = p_x;
}

/*!
 * FresnelIntegral����
 */
FresnelIntegral::~FresnelIntegral()
{

}

/*!
 * \brief ���������������ּ���
 * \param x �Ǹ������������������ֵı߽�
 * \return ���ط������������������ͬ��Ҳ�Ǹ���
 */
std::complex<double> FresnelIntegral::calculate(const std::complex<double> &p_x)
{
    double ls_pi = MATH_PI;
    if(complex_mod(p_x) < 3)    //��ģֵС��3�������̩�ռ���չ��
    {
        return taylor_expand(p_x);
    }else                       //������н���չ��
    {
        boost::optional<double> ls_phase = complex_phase(p_x);
        std::complex<double> ls_res(sqrt(2.0)/2, -sqrt(2.0)/2);
        ls_res *= sqrt(ls_pi)/2;

        if(ls_phase >= ls_pi/4 && ls_phase < 5 * ls_pi/4)
            return -ls_res  - progress_expand(p_x);
        else
            return ls_res - progress_expand(p_x);
    }
}

std::complex<double> FresnelIntegral::reverse_calculate(const std::complex<double> &p_x)
{
    double ls_pi = MATH_PI;
    if(complex_mod(p_x) >= 3)   //��ģֵ����3�����н���չ��
    {
        return progress_expand(p_x);
    }else                       //�������̩��չ��
    {
        boost::optional<double> ls_phase = complex_phase(p_x);
        std::complex<double> ls_res(sqrt(2.0)/2, -sqrt(2.0)/2);
        ls_res *= sqrt(ls_pi)/2;

        if(ls_phase >= ls_pi/4 && ls_phase < 5 * ls_pi/4)
            return -ls_res  - taylor_expand(p_x);
        else
            return ls_res - taylor_expand(p_x);
    }
}


/*!
 * \brief ʹ�ù��캯������ֵ���м���
 * \exception �����캯��δ���ü���߽磬���׳��쳣std::exception
 * \return ���ط������������������ͬ��Ҳ�Ǹ���
 */
std::complex<double> FresnelIntegral::calculate()
{
    //��m_xΪ��ʼ�������׳�δ��ʼ���쳣
    if(!m_x.is_initialized()) throw std::string("uninitialized value");

    return calculate(m_x.get());
}

std::complex<double> FresnelIntegral::resverse_calculate()
{
    //��m_xΪ��ʼ�������׳�δ��ʼ���쳣
    if(!m_x.is_initialized()) throw std::string("uninitialized value");

    return reverse_calculate(m_x.get());
}

/*!
 * \brief ̩�ռ���չ���������������
 * \param x ������
 * \return ����������ֵ
 */
std::complex<double> FresnelIntegral::taylor_expand(const std::complex<double> &p_x)
{
    size_t  ls_n = 0;
    std::complex<double> ls_fresnel(0.0, 0.0);

    std::complex<double> ls_tmp;
    do
    {
        ls_tmp = taylor_general_item(p_x,ls_n++);
        ls_fresnel += ls_tmp;
    }while(complex_mod(ls_tmp) > PRECISION);

    return ls_fresnel;
}

/*!
 * \brief ����������̩��չ����һ������ǵļ��㾫����Ϊ0.000001
 * \param x ������
 * \param n ��n��һ��ʽ
 * \return ��n��һ��ʽ��ֵ���
 */
std::complex<double> FresnelIntegral::taylor_general_item(const std::complex<double> &p_x, size_t p_n)
{
    if(p_n == 0) return p_x;                //����ֱ�ӷ���

    double ls_denominator = 1.0;            //һ����ķ�ĸ

    for(size_t i=1; i<=p_n; i++)
        ls_denominator *= i;

    ls_denominator *=(2*p_n+1);
    std::complex<double> ls_numerator = p_x;            //һ�������
    for(size_t i=0; i<2*p_n; i++) ls_numerator *=p_x;

    //�Ը�����i���з�������
    if(p_n%2==0)
    {
        if((p_n/2)%2 == 0)
        {
            ls_numerator = ls_numerator/ls_denominator;
        }else
        {
            ls_numerator = ls_numerator/(-ls_denominator);
        }

    }else
    {
        if((p_n/2)%2 == 0)
        {
            std::complex<double> ls_tmp = ls_numerator/ls_denominator;
            ls_numerator.real(ls_tmp.imag());
            ls_numerator.imag(-ls_tmp.real());
        }else
        {
            std::complex<double> ls_tmp = ls_numerator/(-ls_denominator);
            ls_numerator.real(ls_tmp.imag());
            ls_numerator.imag(-ls_tmp.real());
        }
    }



    return ls_numerator;
}

/*!
 * \brief ����չ���������������
 * \param x ������
 * \return ����������ֵ
 */
std::complex<double> FresnelIntegral::progress_expand(const std::complex<double> &p_x)
{
    size_t  ls_n = 1;
    std::complex<double> ls_fresnel(0.0, 0.0);

    std::complex<double> ls_tmp = progress_general_item(p_x,ls_n++);
    double ls_last;
    do
    {
        ls_fresnel += ls_tmp;
        ls_last = complex_mod(ls_tmp);
        ls_tmp = progress_general_item(p_x,ls_n++);
    }while(complex_mod(ls_tmp) < ls_last);

    ls_fresnel += 1;

    std::complex<double> ls_power_px = p_x * p_x;
    std::complex<double> ls_power(ls_power_px.imag(), -ls_power_px.real());
    std::complex<double> ls_factor(exp(ls_power.real()) * cos(ls_power.imag()),\
                                   exp(ls_power.real()) * sin(ls_power.imag()));
    ls_fresnel *= ls_factor;
    std::complex<double> ls_px(-p_x.imag() * 2, p_x.real() * 2);

    ls_fresnel = ls_fresnel/ls_px;

    return ls_fresnel;
}

/*!
 *  ����չ��һ����
 * \param p_x   ������
 * \param p_n   ��n��һ��ʽ
 * \return  һ������ֵ���
 */
std::complex<double> FresnelIntegral::progress_general_item(const std::complex<double> &p_x, size_t p_n)
{
    //BOOST_ASSERT(p_n >= 1);

    std::complex<double> ls_tmp = p_x * p_x;
    ls_tmp *= 2;

    std::complex<double> ls_deno_factor(-ls_tmp.imag(), ls_tmp.real());
    std::complex<double> ls_denominator(ls_deno_factor.imag(), ls_deno_factor.real());

    for(size_t i=1; i<p_n; i++) ls_denominator *= ls_deno_factor;


    double ls_fn = 1;
    double ls_fd = 1;

    double ls_numerator = 1;

    for(size_t i=1; i<=(2*p_n-1); i++) ls_fn *= i;

    for(size_t i=1; i<p_n; i++)
    {
        ls_fd *= (2 * i);
    }
    ls_numerator = ls_fn/ls_fd;

    if(p_n%2 == 0)
    {
        ls_denominator = ls_numerator/ls_denominator;
    }else
    {
        ls_denominator = -ls_numerator/ls_denominator;
    }
    return ls_denominator;
}

/*!
 * \brief �����������������
 * \deprecated ��δʵ�֣���Ҫʹ�ô˺���
 * \return
 */
std::complex<double> FresnelIntegral::calculate_erf()
{
    return std::complex<double>();
}

/*!
 * \brief �����������������
 * \deprecated ��δʵ�֣���Ҫʹ�ô˺���
 * \param p_x
 * \return
 */
std::complex<double> FresnelIntegral::calculate_erf(const std::complex<double> &p_x)
{
    return std::complex<double>();
}

/*!
 * ������ģ
 */
double FresnelIntegral::complex_mod(const std::complex<double> &p_x)
{
    return sqrt(p_x.real()*p_x.real() + p_x.imag() * p_x.imag());
}

/*!
 * \brief ����ǣ���Χ0~2*PI��ǰ�պ�
 * \param p_x ������
 * \return �����
 */
boost::optional<double> FresnelIntegral::complex_phase(const std::complex<double> &p_x)
{
    typedef boost::optional<double> opt_type;
    double ls_pi = MATH_PI;

    // δ����
    if(p_x.real() == 0.0 && p_x.imag() == 0.0)
        return opt_type();

    // PI/2
    if(p_x.real() == 0.0 && p_x.imag() > 0)
        return opt_type(ls_pi/2);

    // 3*PI/2
    if(p_x.real() == 0.0 && p_x.imag() < 0)
        return opt_type(ls_pi*3/2);


    double ls_phase = atan(abs(p_x.imag()/p_x.real()));

    // ��һ����
    if(p_x.real() > 0 && p_x.imag() > 0)
        return opt_type(ls_phase);

    // ��������
    if(p_x.real() > 0 && p_x.imag() < 0)
        return opt_type(ls_pi * 2 - ls_phase);

    // �ڶ�����
    if(p_x.real() < 0 && p_x.imag() > 0)
        return opt_type(ls_pi - ls_phase);

    // ��������
    if(p_x.real() < 0 && p_x.imag() < 0)
        return opt_type(ls_pi + ls_phase);

    return opt_type();
}
