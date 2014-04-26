/*
 * Copyright (c) 2014, peelo.net
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <peelo/chrono/time.hpp>
#include <stdexcept>
#if defined(_WIN32)
# include <windows.h>
#else
# include <ctime>
#endif

namespace peelo
{
    time::time(int hour, int minute, int second)
        : m_hour(hour)
        , m_minute(minute)
        , m_second(second)
    {
        if (!is_valid(hour, minute, second))
        {
            throw std::invalid_argument("invalid time value");
        }
    }

    time::time(const time& that)
        : m_hour(that.m_hour)
        , m_minute(that.m_minute)
        , m_second(that.m_second) {}

    time time::now()
    {
#if defined(_WIN32)
        SYSTEMTIME local_time;

        ::GetLocalTime(&local_time);

        return time(local_time.wHour, local_time.wMinute, local_time.wSecond);
#else
        std::time_t ts = std::time(NULL);
        std::tm* tm = std::localtime(&ts);

        if (!tm)
        {
            throw std::runtime_error("localtime() failed");
        }

        return time(tm->tm_hour, tm->tm_min, tm->tm_sec);
#endif
    }

    bool time::is_valid(int hour, int minute, int second)
    {
        return (hour >= 0 && hour < 23)
            && (minute >= 0 && minute < 59)
            && (second >= 0 && second < 59);
    }

    time& time::assign(const time& that)
    {
        return assign(that.m_hour, that.m_minute, that.m_second);
    }

    time& time::assign(int hour, int minute, int second)
    {
        if (!is_valid(hour, minute, second))
        {
            throw std::invalid_argument("invalid time value");
        }
        m_hour = hour;
        m_minute = minute;
        m_second = second;

        return *this;
    }

    bool time::equals(const time& that) const
    {
        return equals(that.m_hour, that.m_minute, that.m_second);
    }

    bool time::equals(int hour, int minute, int second) const
    {
        return m_hour == hour
            && m_minute == minute
            && m_second == second;
    }

    int time::compare(const time& that) const
    {
        return compare(that.m_hour, that.m_minute, that.m_second);
    }

    int time::compare(int hour, int minute, int second) const
    {
        if (m_hour != hour)
        {
            return m_hour > hour ? 1 : -1;
        }
        else if (m_minute != minute)
        {
            return m_minute > minute ? 1 : -1;
        }
        else if (m_second != second)
        {
            return m_second > second ? 1 : -1;
        } else {
            return 0;
        }
    }

    time& time::operator++()
    {
        if (++m_second >= 60)
        {
            m_second = 0;
            if (++m_minute >= 60)
            {
                m_minute = 0;
                if (++m_hour >= 24)
                {
                    m_hour = 0;
                }
            }
        }

        return *this;
    }

    time time::operator++(int)
    {
        time clone(*this);

        if (++m_second >= 60)
        {
            m_second = 0;
            if (++m_minute >= 60)
            {
                m_minute = 0;
                if (++m_hour >= 24)
                {
                    m_hour = 0;
                }
            }
        }

        return clone;
    }

    time& time::operator--()
    {
        if (--m_second < 0)
        {
            m_second = 59;
            if (--m_minute < 0)
            {
                m_minute = 59;
                if (--m_hour < 0)
                {
                    m_hour = 23;
                }
            }
        }

        return *this;
    }

    time time::operator--(int)
    {
        time clone(*this);

        if (--m_second < 0)
        {
            m_second = 59;
            if (--m_minute < 0)
            {
                m_minute = 59;
                if (--m_hour < 0)
                {
                    m_hour = 23;
                }
            }
        }

        return clone;
    }

    std::ostream& operator<<(std::ostream& os, const time& t)
    {
        const int hour = t.hour();
        const int minute = t.minute();
        const int second = t.second();

        if (hour < 10)
        {
            os << '0';
        }
        os << hour << ':';
        if (minute < 10)
        {
            os << '0';
        }
        os << minute << ':';
        if (second < 0)
        {
            os << '0';
        }
        os << second;

        return os;
    }
}
