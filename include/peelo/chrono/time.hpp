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
#ifndef PEELO_CHRONO_TIME_HPP_GUARD
#define PEELO_CHRONO_TIME_HPP_GUARD

#include <iostream>

namespace peelo
{
    /**
     * Time value based on 24 hour clock.
     */
    class time
    {
    public:
        explicit time(int hour = 0, int minute = 0, int second = 0);

        /**
         * Copy constructor.
         */
        time(const time& that);

        /**
         * Returns time value based on system clock.
         */
        static time now();

        static bool is_valid(int hour, int minute, int second);

        /**
         * Returns hour of the day (from 0 to 23).
         */
        inline int hour() const
        {
            return m_hour;
        }

        /**
         * Returns minute of the hour (from 0 to 59).
         */
        inline int minute() const
        {
            return m_minute;
        }

        /**
         * Returns second of the minute (from 0 to 59).
         */
        inline int second() const
        {
            return m_second;
        }

        time& assign(const time& that);
        time& assign(int hour, int minute, int second);

        /**
         * Assignment operator.
         */
        inline time& operator=(const time& that)
        {
            return assign(that);
        }

        bool equals(const time& that) const;
        bool equals(int hour, int minute, int second) const;

        inline bool operator==(const time& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const time& that) const
        {
            return !equals(that);
        }

        int compare(const time& that) const;
        int compare(int hour, int minute, int second) const;

        inline bool operator<(const time& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const time& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const time& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const time& that) const
        {
            return compare(that) >= 0;
        }

        /**
         * Increments time by one second.
         */
        time& operator++();

        /**
         * Increments time by one second.
         */
        time operator++(int);

        /**
         * Decrements time by one second.
         */
        time& operator--();

        /**
         * Decrements time by one second.
         */
        time operator--(int);

    private:
        /** Hour of the day. */
        int m_hour;
        /** Minute of the hour. */
        int m_minute;
        /** Second of the minute. */
        int m_second;
    };

    std::ostream& operator<<(std::ostream&, const time&);
}

#endif /* !PEELO_CHRONO_TIME_HPP_GUARD */
