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
#include <peelo/chrono/month.hpp>
#include <stdexcept>

namespace peelo
{
    const month month::jan(1);
    const month month::feb(2);
    const month month::mar(3);
    const month month::apr(4);
    const month month::may(5);
    const month month::jun(6);
    const month month::jul(7);
    const month month::aug(8);
    const month month::sep(9);
    const month month::oct(10);
    const month month::nov(11);
    const month month::dec(12);

    month::month(int index)
        : m_index(index)
    {
        if (!is_valid(index))
        {
            throw std::invalid_argument("invalid month index");
        }
    }

    month::month(const month& that)
        : m_index(that.m_index) {}

    bool month::is_valid(int index)
    {
        return index >= 1 && index <= 12;
    }

    int month::length(bool leap_year) const
    {
        switch (m_index)
        {
            case 1: return 31;
            case 2: return leap_year ? 29 : 28;
            case 3: return 31;
            case 4: return 30;
            case 5: return 31;
            case 6: return 30;
            case 7: return 31;
            case 8: return 31;
            case 9: return 30;
            case 10: return 31;
            case 11: return 30;
            default: return 31;
        }
    }

    month& month::assign(const month& that)
    {
        m_index = that.m_index;

        return *this;
    }

    bool month::equals(const month& that) const
    {
        return m_index == that.m_index;
    }

    int month::compare(const month& that) const
    {
        return m_index > that.m_index ? 1 : m_index < that.m_index ? -1 : 0;
    }

    month& month::operator++()
    {
        if (m_index < 12)
        {
            ++m_index;
        } else {
            m_index = 1;
        }

        return *this;
    }

    month month::operator++(int)
    {
        const int index = m_index;

        if (m_index < 12)
        {
            ++m_index;
        } else {
            m_index = 1;
        }

        return month(index);
    }

    month& month::operator--()
    {
        if (m_index > 1)
        {
            --m_index;
        } else {
            m_index = 12;
        }

        return *this;
    }

    month month::operator--(int)
    {
        const int index = m_index;

        if (m_index > 1)
        {
            --m_index;
        } else {
            m_index = 12;
        }

        return month(index);
    }

    std::ostream& operator<<(std::ostream& os, const month& m)
    {
        switch (m.index())
        {
            case 1:
                os << "January";
                break;
            case 2:
                os << "February";
                break;
            case 3:
                os << "March";
                break;
            case 4:
                os << "April";
                break;
            case 5:
                os << "May";
                break;
            case 6:
                os << "June";
                break;
            case 7:
                os << "July";
                break;
            case 8:
                os << "August";
                break;
            case 9:
                os << "September";
                break;
            case 10:
                os << "October";
                break;
            case 11:
                os << "November";
                break;
            case 12:
                os << "December";
                break;
        }

        return os;
    }

    std::wostream& operator<<(std::wostream& os, const month& m)
    {
        switch (m.index())
        {
            case 1:
                os << L"January";
                break;
            case 2:
                os << L"February";
                break;
            case 3:
                os << L"March";
                break;
            case 4:
                os << L"April";
                break;
            case 5:
                os << L"May";
                break;
            case 6:
                os << L"June";
                break;
            case 7:
                os << L"July";
                break;
            case 8:
                os << L"August";
                break;
            case 9:
                os << L"September";
                break;
            case 10:
                os << L"October";
                break;
            case 11:
                os << L"November";
                break;
            case 12:
                os << L"December";
                break;
        }

        return os;
    }
}
