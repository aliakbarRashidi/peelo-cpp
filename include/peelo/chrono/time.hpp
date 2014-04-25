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

        inline int hour() const
        {
            return m_hour;
        }

        inline int minute() const
        {
            return m_minute;
        }

        inline int second() const
        {
            return m_second;
        }

        time& assign(const time& that);
        time& assign(int hour, int minute, int second);

        inline time& operator=(const time& that)
        {
            return assign(that);
        }

        bool equals(const time& that) const;

        inline bool operator==(const time& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const time& that) const
        {
            return !equals(that);
        }

        int compare(const time& that) const;

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

    private:
        int m_hour;
        int m_minute;
        int m_second;
    };
}

#endif /* !PEELO_CHRONO_TIME_HPP_GUARD */
