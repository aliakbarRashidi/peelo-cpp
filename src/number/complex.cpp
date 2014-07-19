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
#include <peelo/number/complex.hpp>
#include <cmath>

namespace peelo
{
    complex::complex()
        : m_real(0.0)
        , m_imaginary(0.0) {}

    complex::complex(const complex& that)
        : m_real(that.m_real)
        , m_imaginary(that.m_imaginary) {}

    complex::complex(double real, double imaginary)
        : m_real(real)
        , m_imaginary(imaginary) {}

    complex complex::conj() const
    {
        return complex(m_real, -m_imaginary);
    }

    double complex::norm() const
    {
        return std::sqrt(m_real * m_real + m_imaginary * m_imaginary);
    }

    complex& complex::assign(const complex& that)
    {
        m_real = that.m_real;
        m_imaginary = that.m_imaginary;

        return *this;
    }

    complex& complex::assign(double real, double imaginary)
    {
        m_real = real;
        m_imaginary = imaginary;

        return *this;
    }

    bool complex::equals(const complex& that) const
    {
        return m_real == that.m_real && m_imaginary == that.m_imaginary;
    }

    int complex::compare(const complex& that) const
    {
        if (m_real != that.m_real)
        {
            return m_real < that.m_real ? -1 : 1;
        }
        else if (m_imaginary != that.m_imaginary)
        {
            return m_imaginary < that.m_imaginary ? -1 : 1;
        } else {
            return 0;
        }
    }

    complex complex::operator+(const complex& that) const
    {
        complex result;

        result.m_real = m_real + that.m_real;
        result.m_imaginary = m_imaginary + that.m_imaginary;

        return result;
    }
    
    complex complex::operator+(double n) const
    {
        return operator+(complex(n));
    }

    complex complex::operator-(const complex& that) const
    {
        complex result;

        result.m_real = m_real - that.m_real;
        result.m_imaginary = m_imaginary - that.m_imaginary;

        return result;
    }

    complex complex::operator-(double n) const
    {
        return operator-(complex(n));
    }

    complex complex::operator*(const complex& that) const
    {
        complex result;

        result.m_real = (m_real * that.m_real - m_imaginary * that.m_imaginary);
        result.m_imaginary = (m_real * that.m_imaginary + m_imaginary * that.m_real);

        return result;
    }

    complex complex::operator*(double n) const
    {
        return operator*(complex(n));
    }

    complex complex::operator/(const complex& that) const
    {
        complex result;

        result.m_real = (m_real * that.m_real + m_imaginary * that.m_imaginary)
            / (that.m_real * that.m_real + that.m_imaginary * that.m_imaginary);
        result.m_imaginary = (m_imaginary * that.m_real - m_real * that.m_imaginary)
            / (that.m_real * that.m_real + that.m_imaginary * that.m_imaginary);

        return result;
    }

    complex complex::operator/(double n) const
    {
        return operator/(complex(n));
    }

    complex& complex::operator+=(const complex& that)
    {
        m_real += that.m_real;
        m_imaginary += that.m_imaginary;

        return *this;
    }

    complex& complex::operator+=(double n)
    {
        return operator+=(complex(n));
    }

    complex& complex::operator-=(const complex& that)
    {
        m_real -= that.m_real;
        m_imaginary -= that.m_imaginary;

        return *this;
    }

    complex& complex::operator-=(double n)
    {
        return operator-=(complex(n));
    }

    complex& complex::operator*=(const complex& that)
    {
        double real = (m_real * that.m_real - m_imaginary * that.m_imaginary);
        double imaginary = (m_real * that.m_imaginary + m_imaginary * that.m_real);

        m_real = real;
        m_imaginary = imaginary;

        return *this;
    }

    complex& complex::operator*=(double n)
    {
        return operator*=(complex(n));
    }

    complex& complex::operator/=(const complex& that)
    {
        double real = (m_real * that.m_real + m_imaginary * that.m_imaginary)
            / (that.m_real * that.m_real + that.m_imaginary * that.m_imaginary);
        double imaginary = (m_imaginary * that.m_real - m_real * that.m_imaginary)
            / (that.m_real * that.m_real + that.m_imaginary * that.m_imaginary);

        m_real = real;
        m_imaginary = imaginary;

        return *this;
    }

    complex& complex::operator/=(double n)
    {
        return operator/=(complex(n));
    }

    std::ostream& operator<<(std::ostream& os, const class complex& complex)
    {
        os << complex.real();
        if (complex.imaginary() < 0.0)
        {
            os << '-';
        } else {
            os << '+';
        }
        os << complex.imaginary();

        return os;
    }
}
