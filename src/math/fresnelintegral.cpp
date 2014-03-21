#include "fresnelintegral.h"
#include "MathConstants.h"
#include <string>

/*!
 * FresnelIntegral默认构造器
 */
FresnelIntegral::FresnelIntegral()
{
}



/*!
 * FresnelIntegral 单参数构造器
 * \param x 是复变量，即菲涅尔积分的边界
*/
FresnelIntegral::FresnelIntegral(const std::complex<double> &p_x)
{
    m_x = p_x;
}

/*!
 * FresnelIntegral析构
 */
FresnelIntegral::~FresnelIntegral()
{

}

/*!
 * \brief 单参数菲涅尔积分计算
 * \param x 是复变量，即菲涅尔积分的边界
 * \return 返回菲涅尔计算计算结果，其同样也是复数
 */
std::complex<double> FresnelIntegral::calculate(const std::complex<double> &p_x)
{
    double ls_pi = MATH_PI;
    if(complex_mod(p_x) < 3)    //若模值小于3，则进行泰勒级数展开
    {
        return taylor_expand(p_x);
    }else                       //否则进行渐进展开
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
    if(complex_mod(p_x) >= 3)   //若模值大于3，进行渐进展开
    {
        return progress_expand(p_x);
    }else                       //否则进行泰勒展开
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
 * \brief 使用构造函数传入值进行计算
 * \exception 若构造函数未设置计算边界，则抛出异常std::exception
 * \return 返回菲涅尔计算计算结果，其同样也是复数
 */
std::complex<double> FresnelIntegral::calculate()
{
    //若m_x为初始化，在抛出未初始化异常
    if(!m_x.is_initialized()) throw std::string("uninitialized value");

    return calculate(m_x.get());
}

std::complex<double> FresnelIntegral::resverse_calculate()
{
    //若m_x为初始化，在抛出未初始化异常
    if(!m_x.is_initialized()) throw std::string("uninitialized value");

    return reverse_calculate(m_x.get());
}

/*!
 * \brief 泰勒级数展开法求菲涅尔积分
 * \param x 复变量
 * \return 菲涅尔积分值
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
 * \brief 菲涅尔积分泰勒展开的一般项，考虑的计算精度设为0.000001
 * \param x 复变量
 * \param n 第n项一般式
 * \return 第n项一般式求值结果
 */
std::complex<double> FresnelIntegral::taylor_general_item(const std::complex<double> &p_x, size_t p_n)
{
    if(p_n == 0) return p_x;                //首项直接返回

    double ls_denominator = 1.0;            //一般项的分母

    for(size_t i=1; i<=p_n; i++)
        ls_denominator *= i;

    ls_denominator *=(2*p_n+1);
    std::complex<double> ls_numerator = p_x;            //一般项分子
    for(size_t i=0; i<2*p_n; i++) ls_numerator *=p_x;

    //对复变量i进行分类讨论
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
 * \brief 渐进展开法求菲涅尔积分
 * \param x 复变量
 * \return 菲涅尔积分值
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
 *  渐进展开一般项
 * \param p_x   复变量
 * \param p_n   第n项一般式
 * \return  一般项求值结果
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
 * \brief 误差函数法求菲涅尔积分
 * \deprecated 尚未实现，不要使用此函数
 * \return
 */
std::complex<double> FresnelIntegral::calculate_erf()
{
    return std::complex<double>();
}

/*!
 * \brief 误差函数法求菲涅尔积分
 * \deprecated 尚未实现，不要使用此函数
 * \param p_x
 * \return
 */
std::complex<double> FresnelIntegral::calculate_erf(const std::complex<double> &p_x)
{
    return std::complex<double>();
}

/*!
 * 复数求模
 */
double FresnelIntegral::complex_mod(const std::complex<double> &p_x)
{
    return sqrt(p_x.real()*p_x.real() + p_x.imag() * p_x.imag());
}

/*!
 * \brief 复相角，范围0~2*PI，前闭后开
 * \param p_x 复变量
 * \return 复相角
 */
boost::optional<double> FresnelIntegral::complex_phase(const std::complex<double> &p_x)
{
    typedef boost::optional<double> opt_type;
    double ls_pi = MATH_PI;

    // 未定义
    if(p_x.real() == 0.0 && p_x.imag() == 0.0)
        return opt_type();

    // PI/2
    if(p_x.real() == 0.0 && p_x.imag() > 0)
        return opt_type(ls_pi/2);

    // 3*PI/2
    if(p_x.real() == 0.0 && p_x.imag() < 0)
        return opt_type(ls_pi*3/2);


    double ls_phase = atan(abs(p_x.imag()/p_x.real()));

    // 第一象限
    if(p_x.real() > 0 && p_x.imag() > 0)
        return opt_type(ls_phase);

    // 第四象限
    if(p_x.real() > 0 && p_x.imag() < 0)
        return opt_type(ls_pi * 2 - ls_phase);

    // 第二象限
    if(p_x.real() < 0 && p_x.imag() > 0)
        return opt_type(ls_pi - ls_phase);

    // 第三象限
    if(p_x.real() < 0 && p_x.imag() < 0)
        return opt_type(ls_pi + ls_phase);

    return opt_type();
}
