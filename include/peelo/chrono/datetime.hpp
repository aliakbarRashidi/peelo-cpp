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
                          month_e month = month_jan,
                          int day = 1,
                          int hour = 0,
                          int minute = 0,
                          int second = 0);

        datetime(const date& date, const time& time);

        /**
         * Copy constructor.
         */
        datetime(const datetime& that);

        /**
         * Returns current date and time based on system clock.
         */
        static datetime now();

        inline const class date& date() const
        {
            return m_date;
        }

        inline int year() const
        {
            return m_date.year();
        }

        inline month_e month() const
        {
            return m_date.month();
        }

        inline const class time& time() const
        {
            return m_time;
        }

        inline int day() const
        {
            return m_date.day();
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

        datetime& assign(const datetime& that);
        datetime& assign(const class date& date, const class time& time);

        inline datetime& operator=(const datetime& that)
        {
            return assign(that);
        }

        bool equals(const datetime& that) const;

        inline bool operator==(const datetime& that) const
        {
            return equals(that);
        }

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

    private:
        class date m_date;
        class time m_time;
    };
}

#endif /* !PEELO_CHRONO_DATETIME_HPP_GUARD */
