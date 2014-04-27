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
#ifndef PEELO_CHRONO_WEEKDAY_HPP_GUARD
#define PEELO_CHRONO_WEEKDAY_HPP_GUARD

#include <iostream>

namespace peelo
{
    class weekday
    {
    public:
        /** Monday. */
        static const weekday mon;
        /** Tuesday. */
        static const weekday tue;
        /** Wednesday. */
        static const weekday wed;
        /** Thursday. */
        static const weekday thu;
        /** Friday. */
        static const weekday fri;
        /** Saturday. */
        static const weekday sat;
        /** Sunday. */
        static const weekday sun;

        explicit weekday(int index = 1);

        /**
         * Copy constructor.
         */
        weekday(const weekday& that);

        static bool is_valid(int index);

        inline int index() const
        {
            return m_index;
        }

        weekday& assign(const weekday& that);

        /**
         * Assignment operator.
         */
        inline weekday& operator=(const weekday& that)
        {
            return assign(that);
        }

        bool equals(const weekday& that) const;

        /**
         * Equality testing operator.
         */
        inline bool operator==(const weekday& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const weekday& that) const
        {
            return !equals(that);
        }

        int compare(const weekday& that) const;

        inline bool operator<(const weekday& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const weekday& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const weekday& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const weekday& that) const
        {
            return compare(that) >= 0;
        }

        weekday& operator++();

        weekday operator++(int);

        weekday& operator--();

        weekday operator--(int);

    private:
        int m_index;
    };

    std::ostream& operator<<(std::ostream&, const weekday&);
}

#endif /* !PEELO_CHRONO_WEEKDAY_HPP_GUARD */
