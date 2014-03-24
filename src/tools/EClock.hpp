#ifndef ECLOCK_HPP
#define ECLOCK_HPP
#include <windows.h>
#include <gmp.h>
#include <stdio.h>

std::string to_string(LONGLONG num)
{
    LONGLONG lg = num;
    std::string str_;
    while(lg)
    {
        char buf[2];
        sprintf(buf, "%d", lg%10); lg /= 10;
        str_ += buf;
    }
    std::string res_;
    std::string::reverse_iterator iter = str_.rbegin();
    while(iter != str_.rend())
    {
        res_ += *iter;
        iter++;
    }
    return res_;
}


class EClock
{
public:
    EClock()
    {
        QueryPerformanceFrequency(&m_yun);
        QueryPerformanceCounter(&m_litmp);              //取得高精度运行计数器的数值
        m_begin = m_litmp.QuadPart;                     //开始计时
    }
    ~EClock()
    {
        printf("%e us\n", microsecond());
    }

    void performance_frequency()
    {

    }

    double microsecond()
    {
        QueryPerformanceCounter(&m_litmp);              //取得高精度运行计数器的数值
        m_end = m_litmp.QuadPart;                       //终止计时
        std::string res_d = to_string(m_yun.QuadPart);
        std::string begin = to_string(m_begin);
        std::string end = to_string(m_end);
        mpf_t mpf_begin, mpf_end, mpf_end_begin;
        mpf_init_set_str(mpf_begin, begin.c_str(), 10);
        mpf_init_set_str(mpf_end, end.c_str(), 10);
        mpf_init(mpf_end_begin);
        mpf_sub(mpf_end_begin, mpf_end, mpf_begin);

        mpf_t md, res_;
        mpf_init_set_str(md, res_d.c_str(), 10);
        mpf_init(res_);
        mpf_div(res_, mpf_end_begin, md);
        return mpf_get_d(res_) * 1000000;
    }

    double millisecond()
    {
        QueryPerformanceCounter(&m_litmp);              //取得高精度运行计数器的数值
        m_end = m_litmp.QuadPart;                       //终止计时
        std::string res_d = to_string(m_yun.QuadPart);
        std::string begin = to_string(m_begin);
        std::string end = to_string(m_end);
        mpf_t mpf_begin, mpf_end, mpf_end_begin;
        mpf_init_set_str(mpf_begin, begin.c_str(), 10);
        mpf_init_set_str(mpf_end, end.c_str(), 10);
        mpf_init(mpf_end_begin);
        mpf_sub(mpf_end_begin, mpf_end, mpf_begin);

        mpf_t md, res_;
        mpf_init_set_str(md, res_d.c_str(), 10);
        mpf_init(res_);
        mpf_div(res_, mpf_end_begin, md);
        return mpf_get_d(res_) * 1000;
    }

private:
    LARGE_INTEGER       m_yun;
    LARGE_INTEGER       m_litmp;
    LONGLONG            m_begin;
    LONGLONG            m_end;
};

#endif // ECLOCK_HPP
