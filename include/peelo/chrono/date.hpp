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
#ifndef PEELO_CHRONO_DATE_HPP_GUARD
#define PEELO_CHRONO_DATE_HPP_GUARD

#include <peelo/chrono/month.hpp>
#include <peelo/chrono/weekday.hpp>

namespace peelo
{
    /**
     * Gregorian calendar based date value.
     */
    class date
    {
    public:
        explicit date(int year = 1900, month_e month = month_jan, int day = 1);

        /**
         * Copy constructor.
         */
        date(const date& that);

        /**
         * Returns date value based on system clock.
         */
        static date today();

        /**
         * Returns yesterdays date value based on system clock.
         */
        static date yesterday();

        /**
         * Returns tomorrows date value based on system clock.
         */
        static date tomorrow();

        /**
         * Returns year of the date.
         */
        inline int year() const
        {
            return m_year;
        }

        /**
         * Returns month of the year.
         */
        inline month_e month() const
        {
            return m_month;
        }

        /**
         * Returns day of the month (from 1 to 31) of the date.
         */
        inline int day() const
        {
            return m_day;
        }

        /**
         * Returns weekday for this date.
         */
        weekday_e day_of_week() const;

        /**
         * Returns the day of the year (from 1 to 365 or 366 on leap years) for
         * this date.
         */
        int day_of_year() const;

        /**
         * Returns the number of days in the month (28 or 31) for this date.
         */
        int days_in_month() const;

        /**
         * Returns the number of days in the year (365 or 366) for this date.
         */
        int days_in_year() const;

        /**
         * Returns <code>true</code> if the year represented by the date is a
         * leap year.
         */
        bool is_leap_year() const;

        date& assign(const date& that);
        date& assign(int year, month_e month, int day);

        inline date& operator=(const date& that)
        {
            return assign(that);
        }

        bool equals(const date& that) const;

        inline bool operator==(const date& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const date& that) const
        {
            return !equals(that);
        }

        int compare(const date& that) const;

        inline bool operator<(const date& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const date& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const date& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const date& that) const
        {
            return compare(that) >= 0;
        }

    private:
        /** Year of the date. */
        int m_year;
        /** Month of the year. */
        month_e m_month;
        /** Day of the month. */
        int m_day;
    };
}

#endif /* !PEELO_CHRONO_DATE_HPP_GUARD */