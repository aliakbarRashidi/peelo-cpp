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
#ifndef PEELO_NUMBER_RATIO_HPP_GUARD
#define PEELO_NUMBER_RATIO_HPP_GUARD

#include <peelo/number/inttypes.hpp>
#include <iostream>
#include <stdexcept>

namespace peelo
{
    /**
     * Implementation of rational number.
     */
    class ratio
    {
    public:
        /**
         * Constructs rational number which represents zero.
         */
        ratio();

        /**
         * Copy constructor.
         */
        ratio(const ratio& that);

        /**
         * Constructs new rational number.
         *
         * \param numerator         Numerator part
         * \param denominator       Denominator part
         * \throw std::domain_error If denominator is zero
         */
        explicit ratio(int64_t numerator, int64_t denominator = 1)
            throw(std::domain_error);

        /**
         * Returns denominator.
         */
        inline int64_t denominator() const
        {
            return m_denominator;
        }

        /**
         * Returns numerator.
         */
        inline int64_t numerator() const
        {
            return m_numerator;
        }

        ratio& assign(const ratio& that);

        /**
         * Assignment operator.
         */
        inline ratio& operator=(const ratio& that)
        {
            return assign(that);
        }

        /**
         * Tests whether two rational numbers are equal.
         *
         * \param that Other rational number to test equality with
         */
        bool equals(const ratio& that) const;

        /**
         * Equality testing operator.
         */
        inline bool operator==(const ratio& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const ratio& that) const
        {
            return !equals(that);
        }

        /**
         * Compares two rational numbers against each other.
         *
         * \param that Other rational number to test this one against
         */
        int compare(const ratio& that) const;

        inline bool operator<(const ratio& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const ratio& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const ratio& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const ratio& that) const
        {
            return compare(that) >= 0;
        }

        ratio operator-() const;

        ratio operator+(const ratio& that) const;
        ratio operator+(int64_t n) const;

        ratio operator-(const ratio& that) const;
        ratio operator-(int64_t n) const;

        ratio operator*(const ratio& that) const;
        ratio operator*(int64_t n) const;

        ratio operator/(const ratio& that) const;
        ratio operator/(int64_t n) const;

        ratio& operator+=(const ratio& that);
        ratio& operator+=(int64_t n);

        ratio& operator-=(const ratio& that);
        ratio& operator-=(int64_t n);

        ratio& operator*=(const ratio& that);
        ratio& operator*=(int64_t n);

        ratio& operator/=(const ratio& that);
        ratio& operator/=(int64_t n);

    private:
        /** Numerator. */
        int64_t m_numerator;
        /** Denominator. */
        int64_t m_denominator;
    };

    std::ostream& operator<<(std::ostream&, const ratio&);
}

#endif /* !PEELO_NUMBER_RATIO_HPP_GUARD */
