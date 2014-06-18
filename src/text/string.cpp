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
#include <cstring>

namespace peelo
{
    const string::size_type string::npos = -1;

    string::string()
        : m_offset(0)
        , m_length(0)
        , m_runes(0)
        , m_counter(0) {}

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
        , m_runes(n ? new value_type[n] : 0)
        , m_counter(n ? new unsigned(1) : 0)
    {
        for (size_type i = 0; i < n; ++i)
        {
            m_runes[i] = runes[i];
        }
    }

    string::string(const char* input)
        : m_offset(0)
        , m_length(0)
        , m_runes(0)
        , m_counter(0)
    {
        static const unsigned char utf8_length[256] =
        {
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
            3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,6,6,1,1
        };
        static const unsigned char utf8_mask[6] =
        {
            0x7f,
            0x1f,
            0x0f,
            0x07,
            0x03,
            0x01
        };

        if (input)
        {
            const char* p = input;

            while (*p)
            {
                p += utf8_length[static_cast<int>(*p)];
                ++m_length;
            }
            if (m_length)
            {
                m_counter = new unsigned(1);
                m_runes = new value_type[m_length];
                for (size_type i = 0; i < m_length; ++i)
                {
                    const size_type size = utf8_length[static_cast<int>(*input)];
                    const unsigned char mask = utf8_mask[size - 1];
                    unsigned int result = input[0] & mask;

                    for (size_type j = 1; j < size; ++j)
                    {
                        result <<= 6;
                        result |= input[j] & 0x3f;
                    }
                    m_runes[i] = result;
                    input += size;
                }
            }
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

    string& string::assign(const_reference rune)
    {
        if (m_counter && !--(*m_counter))
        {
            delete m_counter;
            delete[] m_runes;
        }
        m_offset = 0;
        m_length = 1;
        m_runes = new value_type[1];
        m_counter = new unsigned(1);
        m_runes[0] = rune;

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

    string string::concat(const string& that) const
    {
        if (!m_length)
        {
            return that;
        }
        else if (!that.m_length)
        {
            return *this;
        } else {
            string result;

            result.m_length = m_length + that.m_length;
            result.m_runes = new value_type[result.m_length];
            result.m_counter = new unsigned(1);
            std::memcpy(static_cast<void*>(result.m_runes),
                        static_cast<const void*>(m_runes + m_offset),
                        m_length * sizeof(value_type));
            std::memcpy(static_cast<void*>(result.m_runes + m_length),
                        static_cast<const void*>(that.m_runes + that.m_offset),
                        that.m_length * sizeof(value_type));

            return result;
        }
    }

    string string::concat(const_reference c) const
    {
        string result;

        result.m_length = m_length + 1;
        result.m_runes = new value_type[result.m_length];
        result.m_counter = new unsigned(1);
        if (m_length)
        {
            std::memcpy(static_cast<void*>(result.m_runes),
                        static_cast<const void*>(m_runes + m_offset),
                        m_length * sizeof(value_type));
        }
        result.m_runes[m_length] = c;

        return result;
    }

    string string::to_lower() const
    {
        if (m_length)
        {
            string result;

            result.m_length = m_length;
            result.m_runes = new value_type[m_length];
            result.m_counter = new unsigned(1);
            for (size_type i = 0; i < m_length; ++i)
            {
                result.m_runes[i] = m_runes[m_offset + i].to_lower();
            }

            return result;
        } else {
            return string();
        }
    }

    string string::to_upper() const
    {
        if (m_length)
        {
            string result;

            result.m_length = m_length;
            result.m_runes = new value_type[m_length];
            result.m_counter = new unsigned(1);
            for (size_type i = 0; i < m_length; ++i)
            {
                result.m_runes[i] = m_runes[m_offset + i].to_upper();
            }

            return result;
        } else {
            return string();
        }
    }

    bool string::is_alpha() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_alpha())
            {
                return false;
            }
        }

        return true;
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

    bool string::is_space() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_space())
            {
                return false;
            }
        }

        return true;
    }

    vector<char> string::utf8() const
    {
        vector<char> result;
        size_type size = 0;

        for (size_type i = 0; i < m_length; ++i)
        {
            unsigned int r = m_runes[m_offset + i].code();

            if (!(r & 0xffffff80))
            {
                ++size;
            }
            else if (!(r & 0xfffff800))
            {
                size += 2;
            }
            else if (!(r & 0xffff0000))
            {
                size += 3;
            }
            else if (!(r & 0xffe00000))
            {
                size += 4;
            }
        }
        result.reserve(size);
        for (size_type i = 0; i < m_length; ++i)
        {
            unsigned int r = m_runes[m_offset + i].code();

            if (!(r & 0xffffff80))
            {
                result << static_cast<char>(r);
            }
            else if (!(r & 0xfffff800))
            {
                result << static_cast<char>(0xc0 | (r >> 6))
                       << static_cast<char>(0x80 | (r & 0x3f));
            }
            else if (!(r & 0xffff0000))
            {
                result << static_cast<char>(0xe0 | (r >> 12))
                       << static_cast<char>(0x80 | ((r >> 6) & 0x3f))
                       << static_cast<char>(0x80 | (r & 0x3f));
            }
            else if (!(r & 0xffe00000))
            {
                result << static_cast<char>(0xf0 | (r >> 18))
                       << static_cast<char>(0x80 | ((r >> 12) & 0x3f))
                       << static_cast<char>(0x80 | ((r >> 6) & 0x3f))
                       << static_cast<char>(0x80 | (r & 0x3f));
            }
        }
        result.push_back(0);

        return result;
    }

    vector<wchar_t> string::widen() const
    {
        vector<wchar_t> result;

#if defined(_WIN32)
        result.reserve(m_length + 1);
        for (size_type i = 0; i < m_length; ++i)
        {
            const_reference r = m_runes[m_offset + i];

            if (r > 0xffff)
            {
                result << static_cast<wchar_t>(0xd800 + (r.code() >> 10))
                       << static_cast<wchar_t>(0xdc00 + (r.code() & 0x3ff));
            } else {
                result << static_cast<wchar_t>(r.code());
            }
        }
#else
        for (size_type i = 0; i < m_length; ++i)
        {
            const rune::value_type c = m_runes[m_offset + i].code();

            if (c < 0x80)
            {
                result << static_cast<wchar_t>(c);
            }
            else if (c < 0x800)
            {
                result << static_cast<wchar_t>(0xc0 | ((c & 0x7c0)) >> 6)
                       << static_cast<wchar_t>(0x80 | (c & 0x3f));
            }
            else if (c < 0x10000)
            {
                result << static_cast<wchar_t>(0xe0 | ((c & 0xf000) >> 12))
                       << static_cast<wchar_t>(0x80 | ((c & 0xfc0) >> 6))
                       << static_cast<wchar_t>(0x80 | (c & 0x3f));
            } else {
                result << static_cast<wchar_t>(0xf0 | ((c & 0x1c0000) >> 18))
                       << static_cast<wchar_t>(0x80 | ((c & 0x3f000) >> 12))
                       << static_cast<wchar_t>(0x80 | ((c & 0xfc0) >> 6))
                       << static_cast<wchar_t>(0x80 | (c & 0x3f));
            }
        }
#endif
        result << static_cast<wchar_t>(0);

        return result;
    }

    string::size_type string::find(const_reference needle, size_type pos) const
    {
        while (pos < m_length)
        {
            if (m_runes[m_offset + pos] == needle)
            {
                return pos;
            } else {
                ++pos;
            }
        }

        return npos;
    }

    string string::substr(size_type pos, size_type count) const
    {
        string result;

        if (pos >= m_length)
        {
            return result;
        }
        else if (count == npos)
        {
            count = m_length - pos;
        }
        else if (count > m_length)
        {
            count = m_length;
        }
        result.m_offset = m_offset + pos;
        result.m_length = count;
        result.m_runes = m_runes;
        if ((result.m_counter = m_counter))
        {
            ++m_counter[0];
        }

        return result;
    }

    std::ostream& operator<<(std::ostream& stream, const string& s)
    {
        string::size_type size = 0;

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
            else if (c < 0x80)
            {
                ++size;
            }
            else if (c < 0x800)
            {
                size += 2;
            }
            else if (c < 0x10000)
            {
                size += 3;
            } else {
                size += 4;
            }
        }
        if (size > 0)
        {
            vector<unsigned char> v;

            v.reserve(size + 1);
            for (std::string::size_type i = 0; i < s.length(); ++i)
            {
                const rune::value_type c = s[i].code();

                if (c > rune::max.code()
                    || (c & 0xfffe) == 0xfffe
                    || (c >= 0xd800 && c <= 0xdfff)
                    || (c >= 0xffd0 && c <= 0xfdef))
                {
                    continue;
                }
                else if (c < 0x80)
                {
                    v << static_cast<unsigned char>(c);
                }
                else if (c < 0x800)
                {
                    v << static_cast<unsigned char>(0xc0 | ((c & 0x7c0)) >> 6)
                      << static_cast<unsigned char>(0x80 | (c & 0x3f));
                }
                else if (c < 0x10000)
                {
                    v << static_cast<unsigned char>(0xe0 | ((c & 0xf000) >> 12))
                      << static_cast<unsigned char>(0x80 | ((c & 0xfc0) >> 6))
                      << static_cast<unsigned char>(0x80 | (c & 0x3f));
                } else {
                    v << static_cast<unsigned char>(0xf0 | ((c & 0x1c0000) >> 18))
                      << static_cast<unsigned char>(0x80 | ((c & 0x3f000) >> 12))
                      << static_cast<unsigned char>(0x80 | ((c & 0xfc0) >> 6))
                      << static_cast<unsigned char>(0x80 | (c & 0x3f));
                }
            }
            v << static_cast<unsigned char>(0);
            stream << v.data();
        }

        return stream;
    }

    std::wostream& operator<<(std::wostream& stream, const string& s)
    {
        vector<wchar_t> result;

#if defined(_WIN32)
        result.reserve(s.length() + 1);
        for (std::string::size_type i = 0; i < s.length(); ++i)
        {
            const rune::value_type c = s[i].code();

            if (c > rune::max.code()
                || (c & 0xfffe) == 0xfffe
                || (c >= 0xd800 && c <= 0xdfff)
                || (c >= 0xffd0 && c <= 0xfdef))
            {
                continue;
            }
            else if (c > 0xffff)
            {
                result << static_cast<wchar_t>(0xd800 + (c >> 10))
                       << static_cast<wchar_t>(0xdc00 + (c & 0x3ff));
            } else {
                result << static_cast<wchar_t>(c);
            }
        }
#else
        string::size_type size = 0;

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
            else if (c < 0x80)
            {
                ++size;
            }
            else if (c < 0x800)
            {
                size += 2;
            }
            else if (c < 0x10000)
            {
                size += 3;
            } else {
                size += 4;
            }
        }
        result.reserve(size + 1);
        for (std::string::size_type i = 0; i < s.length(); ++i)
        {
            const rune::value_type c = s[i].code();

            if (c > rune::max.code()
                || (c & 0xfffe) == 0xfffe
                || (c >= 0xd800 && c <= 0xdfff)
                || (c >= 0xffd0 && c <= 0xfdef))
            {
                continue;
            }
            else if (c < 0x80)
            {
                result << static_cast<wchar_t>(c);
            }
            else if (c < 0x800)
            {
                result << static_cast<wchar_t>(0xc0 | ((c & 0x7c0)) >> 6)
                       << static_cast<wchar_t>(0x80 | (c & 0x3f));
            }
            else if (c < 0x10000)
            {
                result << static_cast<wchar_t>(0xe0 | ((c & 0xf000) >> 12))
                       << static_cast<wchar_t>(0x80 | ((c & 0xfc0) >> 6))
                       << static_cast<wchar_t>(0x80 | (c & 0x3f));
            } else {
                result << static_cast<wchar_t>(0xf0 | ((c & 0x1c0000) >> 18))
                       << static_cast<wchar_t>(0x80 | ((c & 0x3f000) >> 12))
                       << static_cast<wchar_t>(0x80 | ((c & 0xfc0) >> 6))
                       << static_cast<wchar_t>(0x80 | (c & 0x3f));
            }
        }
#endif
        result << static_cast<wchar_t>(0);
        stream << result.data();

        return stream;
    }
}
