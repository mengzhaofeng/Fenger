#ifndef FRESNELINTEGRAL_H
#define FRESNELINTEGRAL_H

/*!
 * \brief The FresnelIntegral class
 */

/*!
 * \file fresnelintegral.h
 */

/*!
 * \copyright Copyright (C), 2008-2013, Hollywell Electronic System Co.
 */

/*!
 * \author mengzhaofeng
 */

/*!
 * \email m_eagle@163.com
 */

/*!
 * \version 1.0.0
 */

/*!
 * \date 2013-01-20
 */

/*! \mainpage ���������ֵļ���
 *
 * \section ���
 * &nbsp;&nbsp;&nbsp;&nbsp;�ڹ�ѧ�Y��������-�����������乫ʽ��Fresnel-Kirchoff's diffraction formula��
 * ����Ӧ���ڹⲨ���������۷���ģ�ͻ���ֵ����ģ�͡��ӷ�����-�����������乫ʽ��
 * �����Ƶ����ݸ�˹��������ԭ�����ҽ���һЩ�ݸ�˹��������ԭ���޷����͵���������������
 * ������-�����������乫ʽ������Ϊ�������������乫ʽ����Kirchoff's diffraction formula����
 * ��FresnelIntegral��װ�˷��������ֵļ��㣬�㷨Դ���ڡ���������
 * ��ï�⣬���������������ֵļ��㼰�����ʣ����ӿ�ѧѧ��,
 * 1994-11��615-621������
 * <p>&nbsp;&nbsp;&nbsp;&nbsp;<b>�㷨������</b>���ϼ���չ�����ͽ���
 * չ�����������������ƽ���ڵĿ�����ֵ�����ٽ��<b>|x|</b>=3Ϊ�磬�ֱ�
 * ������չ���ͽ���չ����</p>
 */


#include <boost/optional.hpp>
#include <complex>
#include <exception>


#define PRECISION   0.00000001        //���㾫��

/*!
 * \brief FresnelIntegral���ּ�����
 */

/*!
 * ��FresnelIntegral��װ�˷��������ֵļ��㣬�㷨Դ���ڡ���������
 * ��ï�⣬���������������ֵļ��㼰�����ʣ����ӿ�ѧѧ��,
 * 1994-11��615-621���������㾫�ȿɴ�0.00000001��
 */
class FresnelIntegral
{
public:
    //! default constructor.
    FresnelIntegral();

    //! single param constructor.
    FresnelIntegral(const std::complex<double> &p_x);

    //! destruction
    ~FresnelIntegral();
public:
    //! FresnelIntegral ������ֵ
    std::complex<double> calculate(const std::complex<double> &p_x);

    //! FresnelIntegral ������ֵ
    std::complex<double> reverse_calculate(const std::complex<double> &p_x);

    //! FresnelIntegral ������ֵ��ʹ�ù��캯������Ĳ���
    std::complex<double> calculate();

    //! FresnelIntegral ������ֵ��ʹ�ù��캯������Ĳ���
    std::complex<double> resverse_calculate();

    //! ������
    std::complex<double> calculate_erf();

    //! ������
    std::complex<double> calculate_erf(const std::complex<double> &p_x);


private:
    //! ������ģ
    inline double complex_mod(const std::complex<double> &p_x);
    //! ����
    inline boost::optional<double> complex_phase(const std::complex<double> &p_x);
    //! ̩�ռ���չ��
    std::complex<double> taylor_expand(const std::complex<double> &p_x);
    //! ������̩��չ��һ����
    std::complex<double> taylor_general_item(const std::complex<double> &p_x, size_t p_n);
    //! ����չ��
    std::complex<double> progress_expand(const std::complex<double> &p_x);
    //! ����չ��һ����
    std::complex<double> progress_general_item(const std::complex<double> &p_x, size_t p_n);

private:
    //! keep the complex value
    boost::optional<std::complex<double> >   m_x;

};

#endif // FRESNELINTEGRAL_H
