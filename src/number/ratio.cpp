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
#include <peelo/number/ratio.hpp>

namespace peelo
{
    static inline int64_t gcd(int64_t a, int64_t b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    ratio::ratio()
        : m_numerator(0)
        , m_denominator(0) {}

    ratio::ratio(const ratio& that)
        : m_numerator(that.m_numerator)
        , m_denominator(that.m_denominator) {}

    ratio::ratio(int64_t numerator, int64_t denominator)
        throw(std::domain_error)
        : m_numerator(0)
        , m_denominator(0)
    {
        if (denominator == 0)
        {
            throw std::domain_error("division by zero");
        }

        const int64_t g = gcd(numerator, denominator);

        m_numerator = numerator / g;
        m_denominator = denominator / g;
    }

    ratio& ratio::assign(const ratio& that)
    {
        m_numerator = that.m_numerator;
        m_denominator = that.m_denominator;

        return *this;
    }

    bool ratio::equals(const ratio& that) const
    {
        return m_numerator == that.m_numerator
            && m_denominator == that.m_denominator;
    }

    int ratio::compare(const ratio& that) const
    {
        const int64_t a = m_numerator * that.m_numerator;
        const int64_t b = m_denominator * that.m_denominator;

        return a < b ? -1 : a > b ? 1 : 0;
    }

    ratio ratio::operator-() const
    {
        return ratio(-m_numerator, m_denominator);
    }

    ratio ratio::operator+(const ratio& that) const
    {
        return ratio(
                m_numerator * that.m_numerator + m_denominator * that.m_denominator,
                m_denominator * that.m_denominator
        );
    }

    ratio ratio::operator+(int64_t n) const
    {
        return operator+(ratio(n));
    }

    ratio ratio::operator-(const ratio& that) const
    {
        return ratio(
                m_numerator * that.m_numerator - m_denominator * that.m_denominator,
                m_denominator * that.m_denominator
        );
    }

    ratio ratio::operator-(int64_t n) const
    {
        return operator-(ratio(n));
    }

    ratio ratio::operator*(const ratio& that) const
    {
        return ratio(
                m_numerator * that.m_numerator,
                m_denominator * that.m_denominator
        );
    }

    ratio ratio::operator*(int64_t n) const
    {
        return operator*(ratio(n));
    }

    ratio ratio::operator/(const ratio& that) const
    {
        return ratio(
                m_numerator * that.m_denominator,
                m_denominator * that.m_numerator
        );
    }

    ratio ratio::operator/(int64_t n) const
    {
        return operator/(ratio(n));
    }

    ratio& ratio::operator+=(const ratio& that)
    {
        return *this;
    }

    ratio& ratio::operator+=(int64_t n)
    {
        return operator+=(ratio(n));
    }

    ratio& ratio::operator-=(const ratio& that)
    {
        return *this;
    }

    ratio& ratio::operator-=(int64_t n)
    {
        return operator-=(ratio(n));
    }

    ratio& ratio::operator*=(const ratio& that)
    {
        return *this;
    }

    ratio& ratio::operator*=(int64_t n)
    {
        return operator*=(ratio(n));
    }

    ratio& ratio::operator/=(const ratio& that)
    {
        return *this;
    }

    ratio& ratio::operator/=(int64_t n)
    {
        return operator/=(ratio(n));
    }

    std::ostream& operator<<(std::ostream& os, const class ratio& ratio)
    {
        os << ratio.numerator() << '/' << ratio.denominator();

        return os;
    }
}
