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
#ifndef PEELO_CHRONO_MONTH_HPP_GUARD
#define PEELO_CHRONO_MONTH_HPP_GUARD

#include <iostream>

namespace peelo
{
    /**
     * Month value based on Gregorian calendar.
     */
    class month
    {
    public:
        /** January. */
        static const month jan;
        /** February. */
        static const month feb;
        /** March. */
        static const month mar;
        /** April. */
        static const month apr;
        /** May. */
        static const month may;
        /** June. */
        static const month jun;
        /** July. */
        static const month jul;
        /** August. */
        static const month aug;
        /** September. */
        static const month sep;
        /** October. */
        static const month oct;
        /** November. */
        static const month nov;
        /** December. */
        static const month dec;

        explicit month(int index = 1);

        /**
         * Copy constructor.
         */
        month(const month& that);

        static bool is_valid(int index);

        /**
         * Returns numerical index of the month (from 1 to 12).
         */
        inline int index() const
        {
            return m_index;
        }

        /**
         * Returns the number of days in the month (28 to 31).
         */
        int length(bool leap_year) const;

        month& assign(const month& that);

        /**
         * Assignment operator.
         */
        inline month& operator=(const month& that)
        {
            return assign(that);
        }

        bool equals(const month& that) const;

        inline bool operator==(const month& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const month& that) const
        {
            return !equals(that);
        }

        int compare(const month& that) const;

        inline bool operator<(const month& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const month& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const month& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const month& that) const
        {
            return compare(that) >= 0;
        }

        /**
         * Increments month by one.
         */
        month& operator++();

        /**
         * Increments month by one.
         */
        month operator++(int);

        /**
         * Decrements month by one.
         */
        month& operator--();

        /**
         * Decrements month by one.
         */
        month operator--(int);

    private:
        int m_index;
    };

    std::ostream& operator<<(std::ostream&, const month&);
    std::wostream& operator<<(std::wostream&, const month&);
}

#endif /* !PEELO_CHRONO_MONTH_HPP_GUARD */
