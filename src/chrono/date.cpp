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
#include <peelo/chrono/date.hpp>
#include <stdexcept>
#if defined(_WIN32)
# include <windows.h>
#else
# include <ctime>
#endif

namespace peelo
{
    static inline int days_in_month(month_e month, bool is_leap_year)
    {
        switch (month)
        {
            case month_jan: return 31;
            case month_feb: return is_leap_year ? 29 : 28;
            case month_mar: return 31;
            case month_apr: return 30;
            case month_may: return 31;
            case month_jun: return 30;
            case month_jul: return 31;
            case month_aug: return 31;
            case month_sep: return 30;
            case month_oct: return 31;
            case month_nov: return 30;
            default: return 31;
        }
    }

    static inline bool is_leap_year(int year)
    {
        return (year % 4 == 0 && year % 100 == 0) || (year % 400 == 0);
    }

    static inline bool is_valid_date(int year, month_e month, int day)
    {
        return day > 0 && day <= days_in_month(month, is_leap_year(year));
    }

    date::date(int year, month_e month, int day)
        : m_year(year)
        , m_month(month)
        , m_day(day)
    {
        if (!is_valid_date(year, month, day))
        {
            throw std::invalid_argument("invalid date value");
        }
    }

    date::date(const date& that)
        : m_year(that.m_year)
        , m_month(that.m_month)
        , m_day(that.m_day) {}

    date date::today()
    {
#if defined(_WIN32)
        SYSTEMTIME local_time;

        ::GetLocalTime(&local_time);

        return date(
                local_time.wYear,
                static_cast<month_e>(local_time.wMonth),
                local_time.wDay
        );
#else
        std::time_t ts = std::time(NULL);
        std::tm* tm = std::localtime(&ts);

        if (!tm)
        {
            throw std::runtime_error("localtime() failed");
        }

        return date(
                tm->tm_year + 1900,
                static_cast<month_e>(tm->tm_mon + 1),
                tm->tm_mday
        );
#endif
    }

    date date::yesterday()
    {
#if defined(_WIN32)
        SYSTEMTIME local_time;

        ::GetLocalTime(&local_time);
        if (lt.wDay > 1)
        {
            return date(
                    local_time.wYear,
                    static_cast<month_e>(local_time.wMonth),
                    local_time.wDay - 1
            );
        }
        else if (lt.wMonth == 1)
        {
            return date(lt.wYear - 1, month_dec, 31);
        } else {
            month_e month = static_cast<month_e>(lt.wMonth - 1);

            return date(
                    lt.wYear,
                    month,
                    days_in_month(month, peelo::is_leap_year(lt.wYear))
            );
        }
#else
        std::time_t ts = std::time(NULL);
        std::tm* tm = std::localtime(&ts);

        if (!tm)
        {
            throw std::runtime_error("localtime() failed");
        }
        --tm->tm_mday;
        if ((ts = std::mktime(tm)) == -1)
        {
            throw std::runtime_error("mktime() failed");
        }

        return date(
                tm->tm_year + 1900,
                static_cast<month_e>(tm->tm_mon + 1),
                tm->tm_mday
        );
#endif
    }

    date date::tomorrow()
    {
#if defined(_WIN32)
        SYSTEMTIME local_time;

        ::GetLocalTime(&local_time);
        if (lt.wDay == peelo::days_in_month(
                    static_cast<month_e>(lt.wMonth),
                    peelo::is_leap_year(lt.wYear)
        ))
        {
            if (lt.wMonth == month_dec)
            {
                return date(lt.wYear + 1, month_jan, 1);
            } else {
                return date(lt.wYear, static_cast<month_e>(lt.wMonth + 1), 1);
            }
        } else {
            return date(lt.wYear, static_cast<month_e>(lt.wMonth), lt.wDay + 1);
        }
#else
        std::time_t ts = std::time(NULL);
        std::tm* tm = std::localtime(&ts);

        if (!tm)
        {
            throw std::runtime_error("localtime() failed");
        }
        ++tm->tm_mday;
        if ((ts = std::mktime(tm)) == -1)
        {
            throw std::runtime_error("mktime() failed");
        }

        return date(
                tm->tm_year + 1900,
                static_cast<month_e>(tm->tm_mon + 1),
                tm->tm_mday
        );
#endif
    }

    weekday_e date::day_of_week() const
    {
#if defined(_WIN32)
        SYSTEMTIME st;
        FILETIME ft;

        st.wYear = m_year;
        st.wMonth = static_cast<int>(m_month);
        st.wDay = m_day;
        ::SystemTimeToFileTime(&st, &ft);
        ::FileTimeToSystemTime(&ft, &st);
        switch (st.wDayOfWeek)
        {
            case 0: return weekday_sun;
            case 1: return weekday_mon;
            case 2: return weekday_tue;
            case 3: return weekday_wed;
            case 4: return weekday_thu;
            case 5: return weekday_fri;
            case 6: return weekday_sat;
        }
#else
        std::tm tm;

        tm.tm_year = m_year - 1900;
        tm.tm_mon = static_cast<int>(m_month) - 1;
        tm.tm_mday = m_day;
        if (std::mktime(&tm) == -1)
        {
            throw std::runtime_error("mktime() failed");
        }
        switch (tm.tm_wday)
        {
            case 0: return weekday_sun;
            case 1: return weekday_mon;
            case 2: return weekday_tue;
            case 3: return weekday_wed;
            case 4: return weekday_thu;
            case 5: return weekday_fri;
            case 6: return weekday_sat;
        }
#endif

        throw std::runtime_error("unable to determine day of week");
    }

    int date::day_of_year() const
    {
        bool leap_year = is_leap_year();
        int result = 0;

        for (int i = 1; i < m_month; ++i)
        {
            result += peelo::days_in_month(static_cast<month_e>(i), leap_year);
        }

        return result + m_day;
    }

    int date::days_in_month() const
    {
        return peelo::days_in_month(m_month, is_leap_year());
    }

    int date::days_in_year() const
    {
        return is_leap_year() ? 366 : 365;
    }

    bool date::is_leap_year() const
    {
        return peelo::is_leap_year(m_year);
    }

    date& date::assign(const date& that)
    {
        m_year = that.m_year;
        m_month = that.m_month;
        m_day = that.m_day;

        return *this;
    }

    date& date::assign(int year, month_e month, int day)
    {
        if (!is_valid_date(year, month, day))
        {
            throw std::invalid_argument("invalid date value");
        }
        m_year = year;
        m_month = month;
        m_day = day;

        return *this;
    }

    bool date::equals(const date& that) const
    {
        return m_year == that.m_year
            && m_month == that.m_month
            && m_day == that.m_day;
    }

    int date::compare(const date& that) const
    {
        if (m_year != that.m_year)
        {
            return m_year > that.m_year ? 1 : -1;
        }
        else if (m_month != that.m_month)
        {
            return m_month > that.m_month ? 1 : -1;
        }
        else if (m_day != that.m_day)
        {
            return m_day > that.m_day ? 1 : -1;
        } else {
            return 0;
        }
    }
}
