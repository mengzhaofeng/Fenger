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

/*! \mainpage 菲涅尔积分的计算
 *
 * \section 简介
 * &nbsp;&nbsp;&nbsp;&nbsp;在光学裏，菲涅耳-基尔霍夫衍射公式（Fresnel-Kirchoff's diffraction formula）
 * 可以应用于光波传播的理论分析模型或数值分析模型。从菲涅耳-基尔霍夫衍射公式，
 * 可以推导出惠更斯－菲涅耳原理，并且解释一些惠更斯－菲涅耳原理无法解释的物理现象与结果。
 * 菲涅耳-基尔霍夫衍射公式常被称为“基尔霍夫衍射公式”（Kirchoff's diffraction formula）。
 * 类FresnelIntegral封装了菲涅尔积分的计算，算法源自于【吴良超、
 * 汪茂光，复宗量菲涅尔积分的计算及其性质，电子科学学刊,
 * 1994-11（615-621）】。
 * <p>&nbsp;&nbsp;&nbsp;&nbsp;<b>算法简述：</b>联合级数展开法和渐进
 * 展开法，解决在整个复平面内的快速求值，以临界点<b>|x|</b>=3为界，分别
 * 做级数展开和渐进展开。</p>
 */


#include <boost/optional.hpp>
#include <complex>
#include <exception>


#define PRECISION   0.00000001        //计算精度

/*!
 * \brief FresnelIntegral积分计算类
 */

/*!
 * 类FresnelIntegral封装了菲涅尔积分的计算，算法源自于【吴良超、
 * 汪茂光，复宗量菲涅尔积分的计算及其性质，电子科学学刊,
 * 1994-11（615-621）】，计算精度可达0.00000001。
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
    //! FresnelIntegral 下限求值
    std::complex<double> calculate(const std::complex<double> &p_x);

    //! FresnelIntegral 上限求值
    std::complex<double> reverse_calculate(const std::complex<double> &p_x);

    //! FresnelIntegral 下限求值，使用构造函数传入的参数
    std::complex<double> calculate();

    //! FresnelIntegral 上限求值，使用构造函数传入的参数
    std::complex<double> resverse_calculate();

    //! 误差函数法
    std::complex<double> calculate_erf();

    //! 误差函数法
    std::complex<double> calculate_erf(const std::complex<double> &p_x);


private:
    //! 复数求模
    inline double complex_mod(const std::complex<double> &p_x);
    //! 复相
    inline boost::optional<double> complex_phase(const std::complex<double> &p_x);
    //! 泰勒级数展开
    std::complex<double> taylor_expand(const std::complex<double> &p_x);
    //! 菲涅尔泰勒展开一般项
    std::complex<double> taylor_general_item(const std::complex<double> &p_x, size_t p_n);
    //! 渐进展开
    std::complex<double> progress_expand(const std::complex<double> &p_x);
    //! 渐进展开一般项
    std::complex<double> progress_general_item(const std::complex<double> &p_x, size_t p_n);

private:
    //! keep the complex value
    boost::optional<std::complex<double> >   m_x;

};

#endif // FRESNELINTEGRAL_H
