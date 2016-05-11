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
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#else
# include <ctime>
#endif

namespace peelo
{
    date::date(int year, const class month& month, int day)
        : m_year(year)
        , m_month(month)
        , m_day(day)
    {
        if (!is_valid(year, month, day))
        {
            throw std::invalid_argument("invalid date value");
        }
    }

    date::date(const date& that)
        : m_year(that.m_year)
        , m_month(that.m_month)
        , m_day(that.m_day) {}

    date::date(long timestamp)
        : m_year(0)
        , m_month(month::jan)
        , m_day(1)
    {
#if defined(_WIN32)
        FILETIME ft;
        SYSTEMTIME st;
        LONGLONG ll = Int32x32To64(timestamp, 10000000) + 116444736000000000;

        ft.dwLowDateTime = static_cast<DWORD>(ll);
        ft.dwHighDateTime = ll >> 32;
        ::FileTimeToSystemTime(&ft, &st);
        m_year = st.wYear;
        m_month = peelo::month(st.wMonth);
        m_day = st.wDay;
#else
        std::time_t ts = static_cast<std::time_t>(timestamp);
        std::tm* tm = std::localtime(&ts);

        if (!tm)
        {
            throw std::runtime_error("localtime() failed");
        }
        m_year = tm->tm_year + 1900;
        m_month = peelo::month(tm->tm_mon + 1);
        m_day = tm->tm_mday;
#endif
    }

    date date::today()
    {
#if defined(_WIN32)
        SYSTEMTIME local_time;

        ::GetLocalTime(&local_time);

        return date(
                local_time.wYear,
                peelo::month(local_time.wMonth),
                local_time.wDay
        );
#else
        std::time_t ts = std::time(0);
        std::tm* tm = std::localtime(&ts);

        if (!tm)
        {
            throw std::runtime_error("localtime() failed");
        }

        return date(
                tm->tm_year + 1900,
                peelo::month(tm->tm_mon + 1),
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
                    peelo::month(local_time.wMonth),
                    local_time.wDay - 1
            );
        }
        else if (lt.wMonth == 1)
        {
            return date(lt.wYear - 1, month::dec, 31);
        } else {
            class month month(lt.wMonth - 1);

            return date(
                    lt.wYear,
                    month,
                    month.length(is_leap_year(lt.wYear))
            );
        }
#else
        std::time_t ts = std::time(0);
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
                peelo::month(tm->tm_mon + 1),
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
                    month(lt.wMonth),
                    is_leap_year(lt.wYear)
        ))
        {
            if (lt.wMonth == month_dec)
            {
                return date(lt.wYear + 1, month_jan, 1);
            } else {
                return date(lt.wYear, peelo::month(lt.wMonth + 1), 1);
            }
        } else {
            return date(lt.wYear, peelo::month(lt.wMonth), lt.wDay + 1);
        }
#else
        std::time_t ts = std::time(0);
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
                peelo::month(tm->tm_mon + 1),
                tm->tm_mday
        );
#endif
    }

    bool date::is_valid(int year, const class month& month, int day)
    {
        return day > 0 && day <= month.length(is_leap_year(year));
    }

    weekday date::day_of_week() const
    {
#if defined(_WIN32)
        SYSTEMTIME st;
        FILETIME ft;

        st.wYear = m_year;
        st.wMonth = m_month.index();
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

        tm.tm_sec = 0;
        tm.tm_min = 0;
        tm.tm_hour = 0;
        tm.tm_mday = m_day;
        tm.tm_mon = m_month.index() - 1;
        tm.tm_year = m_year - 1900;
        tm.tm_isdst = -1;
        if (std::mktime(&tm) == -1)
        {
            throw std::runtime_error("mktime() failed");
        }
        switch (tm.tm_wday)
        {
            case 0: return weekday::sun;
            case 1: return weekday::mon;
            case 2: return weekday::tue;
            case 3: return weekday::wed;
            case 4: return weekday::thu;
            case 5: return weekday::fri;
            case 6: return weekday::sat;
        }
#endif

        throw std::runtime_error("unable to determine day of week");
    }

    int date::day_of_year() const
    {
        const bool leap_year = is_leap_year(m_year);
        int result = 0;

        for (int i = 1; i < m_month.index(); ++i)
        {
            result += peelo::month(i).length(leap_year);
        }

        return result + m_day;
    }

    int date::days_in_year() const
    {
        return days_in_year(m_year);
    }

    int date::days_in_year(int year)
    {
        return is_leap_year(year) ? 366 : 365;
    }

    bool date::is_leap_year() const
    {
        return is_leap_year(m_year);
    }

    bool date::is_leap_year(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    long date::timestamp() const
    {
        static const int days_before_month[12] =
        {
            0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
        };

        // Compute days in a year
        long days = (m_day - 1) + (days_before_month[m_month.index() - 1]);

        // Leap year adjustment
        if (m_month > month::jan && days_in_year() == 366)
        {
            ++days;
        }

        // Compute days in other years
        if (m_year > 1970)
        {
            for (int y = 1970; y < m_year; ++y)
            {
                days += days_in_year(y);
            }
        }
        else if (m_year < 1970)
        {
            for (int y = 1969; y >= m_year; --y)
            {
                days -= days_in_year(y);
            }
        }

        return days * 86400;
    }

    date& date::assign(const date& that)
    {
        return assign(that.m_year, that.m_month, that.m_day);
    }

    date& date::assign(int year, const class month& month, int day)
    {
        if (!is_valid(year, month, day))
        {
            throw std::invalid_argument("invalid date value");
        }
        m_year = year;
        m_month.assign(month);
        m_day = day;

        return *this;
    }

    bool date::equals(const date& that) const
    {
        return equals(that.m_year, that.m_month, that.m_day);
    }

    bool date::equals(int year, const class month& month, int day) const
    {
        return m_year == year
            && m_month.equals(month)
            && m_day == day;
    }

    int date::compare(const date& that) const
    {
        return compare(that.m_year, that.m_month, that.m_day);
    }

    int date::compare(int year, const class month& month, int day) const
    {
        if (m_year != year)
        {
            return m_year > year ? 1 : -1;
        }
        else if (m_month != month)
        {
            return m_month > month ? 1 : -1;
        }
        else if (m_day != day)
        {
            return m_day > day ? 1 : -1;
        } else {
            return 0;
        }
    }

    date& date::operator++()
    {
        if (m_day == m_month.length(is_leap_year()))
        {
            m_day = 1;
            if (m_month == month::dec)
            {
                ++m_year;
                m_month.assign(month::jan);
            } else {
                ++m_month;
            }
        } else {
            ++m_day;
        }

        return *this;
    }

    date& date::operator--()
    {
        if (m_day > 1)
        {
            --m_day;
        }
        else if (m_month == month::jan)
        {
            --m_year;
            m_month.assign(month::dec);
            m_day = 31;
        } else {
            --m_month;
            m_day = m_month.length(is_leap_year());
        }

        return *this;
    }

    date date::operator++(int)
    {
        date clone(*this);

        if (m_day == m_month.length(is_leap_year()))
        {
            m_day = 1;
            if (m_month == month::dec)
            {
                ++m_year;
                m_month.assign(month::jan);
            } else {
                ++m_month;
            }
        } else {
            ++m_day;
        }

        return clone;
    }

    date date::operator--(int)
    {
        date clone(*this);

        if (m_day > 1)
        {
            --m_day;
        }
        else if (m_month == month::jan)
        {
            --m_year;
            m_month.assign(month::dec);
            m_day = 31;
        } else {
            --m_month;
            m_day = m_month.length(is_leap_year());
        }

        return clone;
    }

    duration date::operator-(const date& that) const
    {
        return duration(0, 0, 0, static_cast<int>(timestamp() - that.timestamp()));
    }

    std::ostream& operator<<(std::ostream& os, const date& d)
    {
        int year = d.year();
        const int month = d.month().index();
        const int day = d.day();

        if (year < 0)
        {
            year = -year - 1;
            os << '-';
        }
        if (year < 1000)
        {
            os << '0';
            if (year < 100)
            {
                os << '0';
                if (year < 10)
                {
                    os << '0';
                }
            }
        }
        os << year << '-';
        if (month < 10)
        {
            os << '0';
        }
        os << month << '-';
        if (day < 10)
        {
            os << '0';
        }
        os << day;

        return os;
    }

    std::wostream& operator<<(std::wostream& os, const date& d)
    {
        int year = d.year();
        const int month = d.month().index();
        const int day = d.day();

        if (year < 0)
        {
            year = -year - 1;
            os << L'-';
        }
        if (year < 1000)
        {
            os << L'0';
            if (year < 100)
            {
                os << L'0';
                if (year < 10)
                {
                    os << L'0';
                }
            }
        }
        os << year << L'-';
        if (month < 10)
        {
            os << L'0';
        }
        os << month << L'-';
        if (day < 10)
        {
            os << L'0';
        }
        os << day;

        return os;
    }
}
