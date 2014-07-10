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
#include <peelo/text/stringbuilder.hpp>

namespace peelo
{
    stringbuilder::stringbuilder(size_type capacity)
        : m_capacity(capacity)
        , m_length(0)
        , m_runes(m_capacity ? new rune[m_capacity] : 0) {}

    stringbuilder::stringbuilder(const stringbuilder& that)
        : m_capacity(that.m_length)
        , m_length(m_capacity)
        , m_runes(m_length ? new rune[m_length] : 0)
    {
        for (size_type i = 0; i < m_length; ++i)
        {
            m_runes[i] = that.m_runes[i];
        }
    }

    stringbuilder::stringbuilder(const string& str)
        : m_capacity(str.length())
        , m_length(m_capacity)
        , m_runes(m_length ? new rune[m_length] : 0)
    {
        for (size_type i = 0; i < m_length; ++i)
        {
            m_runes[i] = str[i];
        }
    }

    stringbuilder::~stringbuilder()
    {
        if (m_runes)
        {
            delete[] m_runes;
        }
    }

    string stringbuilder::str() const
    {
        return string(m_runes, m_length);
    }

    stringbuilder::reference stringbuilder::at(size_type pos)
    {
        if (pos >= m_length)
        {
            throw std::out_of_range("string builder index out of bounds");
        } else {
            return m_runes[pos];
        }
    }

    stringbuilder::const_reference stringbuilder::at(size_type pos) const
    {
        if (pos >= m_length)
        {
            throw std::out_of_range("string builder index out of bounds");
        } else {
            return m_runes[pos];
        }
    }

    void stringbuilder::reserve(size_type n)
    {
        pointer old;

        if (m_capacity >= n)
        {
            return;
        }
        old = m_runes;
        m_capacity = n;
        m_runes = new rune[m_capacity = n];
        for (size_type i = 0; i < m_length; ++i)
        {
            m_runes[i] = old[i];
        }
        if (old)
        {
            delete[] old;
        }
    }

    void stringbuilder::clear()
    {
        m_length = 0;
    }

    void stringbuilder::insert(size_type i, const_reference value)
    {
        insert(i, 1, value);
    }

    void stringbuilder::insert(size_type i,
                               size_type count,
                               const_reference value)
    {
        if (i >= m_length)
        {
            throw std::out_of_range("string builder index out of range");
        }
        else if (!count)
        {
            return;
        }
        else if (!i)
        {
            prepend(count, value);
        }
        else if (i == m_length)
        {
            append(count, value);
        } else {
            if (m_capacity >= m_length + count)
            {
                std::memmove(
                        static_cast<void*>(m_runes + i + count),
                        static_cast<const void*>(m_runes + i),
                        sizeof(value_type) * (m_length - i)
                );
            } else {
                pointer old = m_runes;

                m_runes = new rune[m_length + count];
                for (size_type j = 0; j < i - count; ++j)
                {
                    m_runes[j] = old[j];
                }
                for (size_type j = i; j < m_length; ++j)
                {
                    m_runes[j + count] = old[j];
                }
                if (old)
                {
                    delete[] m_runes;
                }
                m_capacity = m_length + count;
            }
            for (size_type j = 0; j < count; ++j)
            {
                m_runes[i + j] = value;
            }
            m_length += count;
        }
    }

    void stringbuilder::insert(size_type i, const string& str)
    {
        if (i >= m_length)
        {
            throw std::out_of_range("string builder index out of range");
        }
        else if (str.empty())
        {
            return;
        }
        else if (!i)
        {
            prepend(str);
        }
        else if (i == m_length)
        {
            append(str);
        } else {
            size_type count = str.length();

            if (m_capacity >= m_length + count)
            {
                std::memmove(
                        static_cast<void*>(m_runes + i + count),
                        static_cast<const void*>(m_runes + i),
                        sizeof(value_type) * (m_length - i)
                );
            } else {
                pointer old = m_runes;

                m_runes = new rune[m_length + count];
                for (size_type j = 0; j < i - count; ++j)
                {
                    m_runes[j] = old[j];
                }
                for (size_type j = i; j < m_length; ++j)
                {
                    m_runes[j + count] = old[j];
                }
                if (old)
                {
                    delete[] m_runes;
                }
                m_capacity = m_length + count;
            }
            for (size_type j = 0; j < count; ++j)
            {
                m_runes[i + j] = str[j];
            }
            m_length += count;
        }
    }

    void stringbuilder::erase(size_type pos)
    {
        if (pos >= m_length)
        {
            throw std::out_of_range("string builder index out of bounds");
        }
        std::memmove(
                static_cast<void*>(m_runes + pos),
                static_cast<const void*>(m_runes + pos + 1),
                sizeof(value_type) * (--m_length - pos)
        );
    }

    void stringbuilder::append(const_reference value)
    {
        reserve(m_length + 1);
        m_runes[m_length++] = value;
    }

    void stringbuilder::append(size_type count, const_reference value)
    {
        if (count)
        {
            reserve(m_length + count);
            for (size_type i = 0; i < count; ++i)
            {
                m_runes[m_length + i] = value;
            }
            m_length += count;
        }
    }

    void stringbuilder::append(const string& str)
    {
        size_type count = str.length();

        if (count)
        {
            reserve(m_length + count);
            for (size_type i = 0; i < count; ++i)
            {
                m_runes[m_length + i] = str[i];
            }
            m_length += count;
        }
    }

    void stringbuilder::prepend(const_reference value)
    {
        if (m_capacity >= m_length + 1)
        {
            std::memmove(
                    static_cast<void*>(m_runes + 1),
                    static_cast<const void*>(m_runes),
                    sizeof(value_type) * m_length
            );
        } else {
            pointer old = m_runes;

            m_runes = new rune[m_capacity + 1];
            for (size_type i = 0; i < m_length; ++i)
            {
                m_runes[i] = old[i];
            }
            if (old)
            {
                delete[] m_runes;
            }
            ++m_capacity;
        }
        m_runes[0] = value;
        ++m_length;
    }

    void stringbuilder::prepend(size_type count, const_reference value)
    {
        if (!count)
        {
            return;
        }
        else if (m_capacity >= m_length + count)
        {
            std::memmove(
                    static_cast<void*>(m_runes + count),
                    static_cast<const void*>(m_runes),
                    sizeof(value_type) * m_length
            );
        } else {
            pointer old = m_runes;

            m_runes = new rune[m_capacity += count];
            for (size_type i = 0; i < m_length; ++i)
            {
                m_runes[count + i] = old[i];
            }
            if (old)
            {
                delete[] old;
            }
        }
        for (size_type i = 0; i < count; ++i)
        {
            m_runes[i] = value;
        }
        m_length += count;
    }

    void stringbuilder::prepend(const string& str)
    {
        size_type count = str.length();

        if (!count)
        {
            return;
        }
        else if (m_capacity >= m_length + count)
        {
            std::memmove(
                    static_cast<void*>(m_runes + count),
                    static_cast<const void*>(m_runes),
                    sizeof(value_type) * m_length
            );
        } else {
            pointer old = m_runes;

            m_runes = new rune[m_capacity += count];
            for (size_type i = 0; i < m_length; ++i)
            {
                m_runes[count + i] = old[i];
            }
            if (old)
            {
                delete[] old;
            }
        }
        for (size_type i = 0; i < count; ++i)
        {
            m_runes[i] = str[i];
        }
        m_length += count;
    }

    bool stringbuilder::equals(const stringbuilder& that) const
    {
        if (m_runes == that.m_runes)
        {
            return true;
        }
        else if (m_length != that.m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (m_runes[i] != that.m_runes[i])
            {
                return false;
            }
        }

        return true;
    }

    bool stringbuilder::equals(const string& str) const
    {
        if (m_length != str.length())
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (m_runes[i] != str[i])
            {
                return false;
            }
        }

        return true;
    }

    stringbuilder& stringbuilder::assign(const stringbuilder& that)
    {
        if (m_runes != that.m_runes)
        {
            if (m_capacity < that.m_length)
            {
                if (m_runes)
                {
                    delete[] m_runes;
                }
                m_runes = new rune[m_capacity = that.m_length];
            }
            for (size_type i = 0; i < that.m_length; ++i)
            {
                m_runes[i] = that.m_runes[i];
            }
            m_length = that.m_length;
        }

        return *this;
    }

    stringbuilder& stringbuilder::assign(const string& str)
    {
        size_type count = str.length();

        if (m_capacity < count)
        {
            if (m_runes)
            {
                delete[] m_runes;
            }
            m_runes = new rune[m_capacity = count];
        }
        for (size_type i = 0; i < count; ++i)
        {
            m_runes[i] = str[i];
        }
        m_length = count;

        return *this;
    }
}
