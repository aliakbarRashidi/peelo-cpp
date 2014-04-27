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
#ifndef PEELO_CHRONO_DURATION_HPP_GUARD
#define PEELO_CHRONO_DURATION_HPP_GUARD

namespace peelo
{
    /**
     * Duration represents a time span measured in seconds.
     */
    class duration
    {
    public:
        static const int hours_per_day;
        static const int minutes_per_day;
        static const int minutes_per_hour;
        static const int seconds_per_day;
        static const int seconds_per_hour;
        static const int seconds_per_minute;

        explicit duration(int days = 0,
                          int hours = 0,
                          int minutes = 0,
                          int seconds = 0);

        /**
         * Copy constructor.
         */
        duration(const duration& that);

        /**
         * Returns duration in days. Incomplete days are discarded.
         */
        inline int days() const
        {
            return m_seconds / seconds_per_day;
        }

        /**
         * Returns duration in hours. Incomplete hours are discarded. The returned
         * value can be greater than 23.
         */
        inline int hours() const
        {
            return m_seconds / seconds_per_hour;
        }

        /**
         * Returns duration in minutes. Incomplete minutes are discarded. The
         * returned value can be greater than 59.
         */
        inline int minutes() const
        {
            return m_seconds / seconds_per_minute;
        }

        /**
         * Returns duration in seconds. The returned value can be greater than
         * 59.
         */
        inline int seconds() const
        {
            return m_seconds;
        }

        duration& assign(const duration& that);

        inline duration& operator=(const duration& that)
        {
            return assign(that);
        }

        bool equals(const duration& that) const;

        inline bool operator==(const duration& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const duration& that) const
        {
            return !equals(that);
        }

        int compare(const duration& that) const;

        inline bool operator<(const duration& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const duration& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const duration& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const duration& that) const
        {
            return compare(that) >= 0;
        }

        duration operator+(const duration& that) const;
        duration operator-(const duration& that) const;
        duration operator*(int factor) const;
        duration operator/(int quotient) const;

    private:
        int m_seconds;
    };
}

#endif /* !PEELO_CHRONO_DURATION_HPP_GUARD */
