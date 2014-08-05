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
        int days() const;

        /**
         * Returns duration in hours. Incomplete hours are discarded. The returned
         * value can be greater than 23.
         */
        int hours() const;

        /**
         * Returns duration in minutes. Incomplete minutes are discarded. The
         * returned value can be greater than 59.
         */
        int minutes() const;

        /**
         * Returns duration in seconds. The returned value can be greater than
         * 59.
         */
        inline int seconds() const
        {
            return m_seconds;
        }

        /**
         * Replaces value of the duration with value from another duration.
         *
         * \param that Other duration to copy value from
         */
        duration& assign(const duration& that);

        /**
         * Assignment operator.
         */
        inline duration& operator=(const duration& that)
        {
            return assign(that);
        }

        /**
         * Tests whether two duration values are equal.
         *
         * \param that Other duration value to test against
         */
        bool equals(const duration& that) const;

        /**
         * Equality testing operator.
         */
        inline bool operator==(const duration& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const duration& that) const
        {
            return !equals(that);
        }

        /**
         * Compares value of duration with another duration.
         *
         * \param that Other duration to compare value against
         */
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
        /** Value of duration in seconds. */
        int m_seconds;
    };
}

#endif /* !PEELO_CHRONO_DURATION_HPP_GUARD */
