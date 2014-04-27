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
#include <peelo/chrono/weekday.hpp>
#include <stdexcept>

namespace peelo
{
    const weekday weekday::mon(1);
    const weekday weekday::tue(2);
    const weekday weekday::wed(3);
    const weekday weekday::thu(4);
    const weekday weekday::fri(5);
    const weekday weekday::sat(6);
    const weekday weekday::sun(7);

    weekday::weekday(int index)
        : m_index(index)
    {
        if (!is_valid(index))
        {
            throw std::invalid_argument("invalid weekday index");
        }
    }

    weekday::weekday(const weekday& that)
        : m_index(that.m_index) {}

    bool weekday::is_valid(int index)
    {
        return index >= 1 && index <= 7;
    }

    weekday& weekday::assign(const weekday& that)
    {
        m_index = that.m_index;

        return *this;
    }

    bool weekday::equals(const weekday& that) const
    {
        return m_index == that.m_index;
    }

    int weekday::compare(const weekday& that) const
    {
        return m_index > that.m_index ? 1 : m_index < that.m_index ? -1 : 0;
    }

    weekday& weekday::operator++()
    {
        if (m_index < 7)
        {
            ++m_index;
        } else {
            m_index = 1;
        }

        return *this;
    }

    weekday weekday::operator++(int)
    {
        const int index = m_index;

        if (m_index < 7)
        {
            ++m_index;
        } else {
            m_index = 1;
        }

        return weekday(index);
    }

    weekday& weekday::operator--()
    {
        if (m_index > 1)
        {
            --m_index;
        } else {
            m_index = 7;
        }

        return *this;
    }

    weekday weekday::operator--(int)
    {
        const int index = m_index;

        if (m_index > 1)
        {
            --m_index;
        } else {
            m_index = 7;
        }

        return weekday(index);
    }
}
