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
#ifndef PEELO_CHRONO_DATETIME_HPP_GUARD
#define PEELO_CHRONO_DATETIME_HPP_GUARD

#include <peelo/chrono/date.hpp>
#include <peelo/chrono/time.hpp>

namespace peelo
{
    class datetime
    {
    public:
        explicit datetime(int year = 1900,
                          const class month& month = month::jan,
                          int day = 1,
                          int hour = 0,
                          int minute = 0,
                          int second = 0);

        /**
         * Copy constructor.
         */
        datetime(const datetime& that);

        datetime(const date& date, const time& time);

        datetime(const date& date);

        datetime(const time& time);

        /**
         * Constructs datetime instance from UNIX timestamp.
         */
        datetime(long timestamp);

        /**
         * Returns current date and time based on system clock.
         */
        static datetime now();

        static bool is_valid(int year,
                             const class month& month,
                             int day,
                             int hour,
                             int minute,
                             int second);

        /**
         * Returns date value.
         */
        inline const class date& date() const
        {
            return m_date;
        }

        /**
         * Returns year of the date.
         */
        inline int year() const
        {
            return m_date.year();
        }

        /**
         * Returns month of the year.
         */
        inline const class month& month() const
        {
            return m_date.month();
        }

        /**
         * Returns day of the month (from 1 to 31) of the date.
         */
        inline int day() const
        {
            return m_date.day();
        }

        /**
         * Returns weekday for this date.
         */
        inline const weekday& day_of_week() const
        {
            return m_date.day_of_week();
        }

        /**
         * Returns the day of the year (from 1 to 365 or 366 on leap years) for
         * this date.
         */
        inline int day_of_year() const
        {
            return m_date.day_of_year();
        }

        /**
         * Returns the number of days in the year (365 or 366) for this date.
         */
        inline int days_in_year() const
        {
            return m_date.days_in_year();
        }

        /**
         * Returns <code>true</code> if the year represented by the date is a
         * leap year.
         */
        inline bool is_leap_year() const
        {
            return m_date.is_leap_year();
        }

        /**
         * Returns time value.
         */
        inline const class time& time() const
        {
            return m_time;
        }

        inline int hour() const
        {
            return m_time.hour();
        }

        inline int minute() const
        {
            return m_time.minute();
        }

        inline int second() const
        {
            return m_time.second();
        }

        /**
         * Calculates UNIX timestamp from date and time.
         */
        long timestamp() const;

        datetime& assign(const datetime& that);
        datetime& assign(const class date& date, const class time& time);

        /**
         * Assignment operator.
         */
        inline datetime& operator=(const datetime& that)
        {
            return assign(that);
        }

        bool equals(const datetime& that) const;

        /**
         * Equality operator.
         */
        inline bool operator==(const datetime& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality operator.
         */
        inline bool operator!=(const datetime& that) const
        {
            return !equals(that);
        }

        int compare(const datetime& that) const;

        inline bool operator<(const datetime& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const datetime& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const datetime& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const datetime& that) const
        {
            return compare(that) >= 0;
        }

        /**
         * Increments date by one day.
         */
        datetime& operator++();

        /**
         * Increments date by one day.
         */
        datetime operator++(int);

        /**
         * Decrements date by one day.
         */
        datetime& operator--();

        /**
         * Decrements date by one day.
         */
        datetime operator--(int);

        datetime operator+(const class duration& duration) const;
        datetime operator-(const class duration& duration) const;

        duration operator-(const datetime& that) const;

    private:
        class date m_date;
        class time m_time;
    };

    std::ostream& operator<<(std::ostream&, const datetime&);
    std::wostream& operator<<(std::wostream&, const datetime&);
}

#endif /* !PEELO_CHRONO_DATETIME_HPP_GUARD */
