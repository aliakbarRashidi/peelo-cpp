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
#include <peelo/chrono/datetime.hpp>
#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
# include <ctime>
#endif

namespace peelo
{
    datetime::datetime(int year,
                       const class month& month,
                       int day,
                       int hour,
                       int minute,
                       int second)
        : m_date(year, month, day)
        , m_time(hour, minute, second) {}

    datetime::datetime(const datetime& that)
        : m_date(that.m_date)
        , m_time(that.m_time) {}

    datetime::datetime(const class date& date, const class time& time)
        : m_date(date)
        , m_time(time) {}

    datetime::datetime(const class date& date)
        : m_date(date) {}

    datetime::datetime(const class time& time)
        : m_time(time) {}

    datetime::datetime(long timestamp)
    {
#if defined(_WIN32)
        FILETIME ft;
        SYSTEMTIME st;
        LONGLONG ll = Int32x32To64(timestamp, 10000000) + 116444736000000000;

        ft.dwLowDateTime = static_cast<DWORD>(ll);
        ft.dwHighDateTime = ll >> 32;
        ::FileTimeToSystemTime(&ft, &st);
        m_date.assign(st.wYear, peelo::month(st.wMonth), st.wDay);
        m_time.assign(st.wHour, st.wMinute, st.wSecond);
#else
        std::time_t ts = static_cast<std::time_t>(timestamp);
        std::tm* tm = std::localtime(&ts);

        if (!tm)
        {
            throw std::runtime_error("localtime() failed");
        }
        m_date.assign(tm->tm_year + 1900, peelo::month(tm->tm_mon + 1), tm->tm_mday);
        m_time.assign(tm->tm_hour, tm->tm_min, tm->tm_sec);
#endif
    }

    datetime datetime::now()
    {
        return datetime(date::today(), time::now());
    }

    bool datetime::is_valid(int year,
                            const class month& month,
                            int day,
                            int hour,
                            int minute,
                            int second)
    {
        return date::is_valid(year, month, day)
            && time::is_valid(hour, minute, second);
    }

    long datetime::timestamp() const
    {
        static const int days_before_month[12] =
        {
            0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
        };

        // Compute hours, minutes and seconds
        long time = m_time.second()
                    + (m_time.minute() * 60)
                    + (m_time.hour() * 3600);

        // Compute days in a year
        long days = (m_date.day() - 1)
                    + (days_before_month[m_date.month().index() - 1]);

        // Leap year adjustment
        if (m_date.month() > month::jan && m_date.days_in_year() == 366)
        {
            ++days;
        }

        // Compute days in other years
        if (m_date.year() > 1970)
        {
            for (int y = 1970; y < m_date.year(); ++y)
            {
                days += date::days_in_year(y);
            }
        }
        else if (m_date.year() < 1970)
        {
            for (int y = 1969; y >= m_date.year(); ++y)
            {
                days -= date::days_in_year(y);
            }
        }
    
        return time + (days * 86400);
    }

    datetime& datetime::assign(const datetime& that)
    {
        m_date.assign(that.m_date);
        m_time.assign(that.m_time);

        return *this;
    }

    datetime& datetime::assign(const class date& date, const class time& time)
    {
        m_date.assign(date);
        m_time.assign(time);

        return *this;
    }

    bool datetime::equals(const datetime& that) const
    {
        return m_date.equals(that.m_date) && m_time.equals(that.m_time);
    }

    int datetime::compare(const datetime& that) const
    {
        int cmp = m_date.compare(that.m_date);

        if (cmp != 0)
        {
            return cmp;
        } else {
            return m_time.compare(that.m_time);
        }
    }

    datetime datetime::operator+(const class duration& duration) const
    {
        return datetime(timestamp() + duration.seconds());
    }

    datetime datetime::operator-(const class duration& duration) const
    {
        return datetime(timestamp() - duration.seconds());
    }

    std::ostream& operator<<(std::ostream& os, const datetime& dt)
    {
        os << dt.date() << ' ' << dt.time() << " UTC";

        return os;
    }
}
