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
#ifndef PEELO_NUMBER_COMPLEX_HPP_GUARD
#define PEELO_NUMBER_COMPLEX_HPP_GUARD

#include <iostream>

namespace peelo
{
    /**
     * Implementation of complex number.
     */
    class complex
    {
    public:
        /**
         * Constructs complex number which represents zero.
         */
        complex();

        /**
         * Copy constructor.
         */
        complex(const complex& that);

        /**
         * Constructs complex number from given two numbers.
         */
        explicit complex(double real, double imaginary = 0.0);

        inline double real() const
        {
            return m_real;
        }

        inline double imaginary() const
        {
            return m_imaginary;
        }

        /**
         * Returns conjugate of complex number.
         */
        complex conj() const;

        /**
         * Returns the norm of the complex number.
         */
        double norm() const;

        complex& assign(const complex& that);
        complex& assign(double real, double imaginary = 0.0);

        /**
         * Assignment operator.
         */
        inline complex& operator=(const complex& that)
        {
            return assign(that);
        }

        /**
         * Assignment operator.
         */
        inline complex& operator=(double n)
        {
            return assign(n);
        }

        /**
         * Tests whether two complex numbers are equal.
         */
        bool equals(const complex& that) const;

        /**
         * Equality testing operator.
         */
        inline bool operator==(const complex& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const complex& that) const
        {
            return !equals(that);
        }

        /**
         * Compares two complex numbers against each other.
         */
        int compare(const complex& that) const;

        inline bool operator<(const complex& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const complex& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const complex& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const complex& that) const
        {
            return compare(that) >= 0;
        }

        complex operator+(const complex& that) const;
        complex operator+(double n) const;

        complex operator-(const complex& that) const;
        complex operator-(double n) const;

        complex operator*(const complex& that) const;
        complex operator*(double n) const;

        complex operator/(const complex& that) const;
        complex operator/(double n) const;

        complex& operator+=(const complex& that);
        complex& operator+=(double n);

        complex& operator-=(const complex& that);
        complex& operator-=(double n);

        complex& operator*=(const complex& that);
        complex& operator*=(double n);

        complex& operator/=(const complex& that);
        complex& operator/=(double n);

    private:
        double m_real;
        double m_imaginary;
    };

    std::ostream& operator<<(std::ostream&, const complex&);
}

#endif /* !PEELO_NUMBER_COMPLEX_HPP_GUARD */
