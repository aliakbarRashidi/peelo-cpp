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
#include <peelo/text/string.hpp>
#include <stdexcept>

namespace peelo
{
    const string::size_type string::npos = -1;

    string::string()
        : m_offset(0)
        , m_length(0)
        , m_runes(NULL)
        , m_counter(NULL) {}

    string::string(const string& that)
        : m_offset(that.m_offset)
        , m_length(that.m_length)
        , m_runes(that.m_runes)
        , m_counter(that.m_counter)
    {
        if (m_counter)
        {
            ++(*m_counter);
        }
    }

    string::string(const_pointer runes, size_type n)
        : m_offset(0)
        , m_length(n)
        , m_runes(n ? new value_type[n] : NULL)
        , m_counter(n ? new unsigned(1) : NULL)
    {
        for (size_type i = 0; i < n; ++i)
        {
            m_runes[i] = runes[i];
        }
    }

    string::~string()
    {
        if (m_counter && !--(*m_counter))
        {
            delete m_counter;
            delete[] m_runes;
        }
    }

    string::const_reference string::front() const
    {
        if (m_length)
        {
            return m_runes[m_offset];
        } else {
            throw std::out_of_range("string is empty");
        }
    }

    string::const_reference string::back() const
    {
        if (m_length)
        {
            return m_runes[m_offset + m_length - 1];
        } else {
            throw std::out_of_range("string is empty");
        }
    }

    string::const_reference string::at(size_type pos) const
    {
        if (m_length && pos < m_length)
        {
            return m_runes[m_offset + pos];
        } else {
            throw std::out_of_range("index out of bounds");
        }
    }

    string& string::assign(const string& that)
    {
        if (m_runes != that.m_runes)
        {
            if (m_counter && !--(*m_counter))
            {
                delete m_counter;
                delete[] m_runes;
            }
            m_runes = that.m_runes;
            if ((m_counter = that.m_counter))
            {
                ++(*m_counter);
            }
        }
        m_offset = that.m_offset;
        m_length = that.m_length;

        return *this;
    }

    bool string::equals(const string& that) const
    {
        if (m_runes == that.m_runes)
        {
            return m_offset == that.m_offset && m_length == that.m_length;
        }
        else if (m_length != that.m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].equals(that.m_runes[that.m_offset + i]))
            {
                return false;
            }
        }

        return true;
    }

    bool string::equals_icase(const string& that) const
    {
        if (m_runes == that.m_runes)
        {
            return m_offset == that.m_offset && m_length == that.m_length;
        }
        else if (m_length != that.m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].equals_icase(that.m_runes[that.m_offset + i]))
            {
                return false;
            }
        }

        return true;
    }

    string string::to_lower() const
    {
        if (m_length)
        {
            value_type result[m_length];

            for (size_type i = 0; i < m_length; ++i)
            {
                result[i] = m_runes[m_offset + i].to_lower();
            }

            return string(result, m_length);
        } else {
            return string();
        }
    }

    string string::to_upper() const
    {
        if (m_length)
        {
            value_type result[m_length];

            for (size_type i = 0; i < m_length; ++i)
            {
                result[i] = m_runes[m_offset + i].to_upper();
            }

            return string(result, m_length);
        } else {
            return string();
        }
    }

    bool string::is_ascii() const
    {
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_ascii())
            {
                return false;
            }
        }

        return true;
    }

    std::ostream& operator<<(std::ostream& stream, const string& s)
    {
        const std::streamsize size = stream.width();

        if (((stream.flags() & std::ios_base::right)
            || (stream.flags() & std::ios_base::internal))
            && size > static_cast<std::streamsize>(s.length()))
        {
            for (std::streamsize i = s.length(); i < size; ++i)
            {
                stream << stream.fill();
            }
        }
        for (string::size_type i = 0; i < s.length(); ++i)
        {
            const rune::value_type c = s[i].code();

            if (c > rune::max.code()
                || (c & 0xfffe) == 0xfffe
                || (c >= 0xd800 && c <= 0xdfff)
                || (c >= 0xffd0 && c <= 0xfdef))
            {
                continue;
            }
            if (c < 0x80)
            {
                stream << static_cast<unsigned char>(c);
            }
            else if (c < 0x800)
            {
                stream << static_cast<unsigned char>(0xc0 | ((c & 0x7c0) >> 6))
                       << static_cast<unsigned char>(0x80 | (c & 0x3f));
            }
            else if (c < 0x10000)
            {
                stream << static_cast<unsigned char>(0xe0 | ((c & 0xf000) >> 12))
                       << static_cast<unsigned char>(0x80 | ((c & 0xfc0) >> 6))
                       << static_cast<unsigned char>(0x80 | (c & 0x3f));
            } else {
                stream << static_cast<unsigned char>(0xf0 | ((c & 0x1c0000) >> 18))
                       << static_cast<unsigned char>(0x80 | ((c & 0x3f000) >> 12))
                       << static_cast<unsigned char>(0x80 | ((c & 0xfc0) >> 6))
                       << static_cast<unsigned char>(0x80 | (c & 0x3f));
            }
        }
        if ((stream.flags() & std::ios_base::left)
            && size > static_cast<std::streamsize>(s.length()))
        {
            for (std::streamsize i = s.length(); i < size; ++i)
            {
                stream << stream.fill();
            }
        }

        return stream;
    }
}
