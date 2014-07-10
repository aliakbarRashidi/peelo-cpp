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
#include <peelo/algorithm/abs.hpp>
#include <peelo/algorithm/min.hpp>
#include <peelo/text/stringbuilder.hpp>
#include <stdexcept>
#include <cstring>

namespace peelo
{
    static const char digitmap[] = "0123456789abcdefghijklmnopqrstuvwxyz";

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

    string::iterator string::begin() const
    {
        iterator i;

        if (m_runes)
        {
            i.m_pointer = m_runes + m_offset;
        }

        return i;
    }

    string::iterator string::end() const
    {
        iterator i;

        if (m_runes)
        {
            i.m_pointer = m_runes + m_offset + m_length;
        }

        return i;
    }

    string::reverse_iterator string::rbegin() const
    {
        return reverse_iterator(end());
    }

    string::reverse_iterator string::rend() const
    {
        return reverse_iterator(begin());
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

    void string::clear()
    {
        if (m_counter && !--(*m_counter))
        {
            delete m_counter;
            delete[] m_runes;
        }
        m_offset = m_length = 0;
        m_runes = 0;
        m_counter = 0;
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

    int string::compare(const string& that) const
    {
        if (m_runes != that.m_runes)
        {
            const size_type n = min(m_length, that.m_length);

            for (size_type i = 0; i < n; ++i)
            {
                const_reference a = m_runes[m_offset + i];
                const_reference b = that.m_runes[that.m_offset + i];

                if (a > b)
                {
                    return 1;
                }
                else if (a < b)
                {
                    return -1;
                }
            }
        }
        if (m_length > that.m_length)
        {
            return 1;
        }
        else if (m_length < that.m_length)
        {
            return -1;
        } else {
            return 0;
        }
    }

    int string::compare_icase(const string& that) const
    {
        if (m_runes != that.m_runes)
        {
            const size_type n = min(m_length, that.m_length);

            for (size_type i = 0; i < n; ++i)
            {
                const value_type a = m_runes[m_offset + i].to_lower();
                const value_type b = that.m_runes[that.m_offset + i].to_lower();

                if (a > b)
                {
                    return 1;
                }
                else if (a < b)
                {
                    return -1;
                }
            }
        }
        if (m_length > that.m_length)
        {
            return 1;
        }
        else if (m_length < that.m_length)
        {
            return -1;
        } else {
            return 0;
        }
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

    bool string::is_alnum() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_alnum())
            {
                return false;
            }
        }

        return true;
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

    bool string::is_blank() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_blank())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_cntrl() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_cntrl())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_digit() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_digit())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_graph() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_graph())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_lower() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_lower())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_number() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_number())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_print() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_print())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_punct() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_punct())
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

    bool string::is_upper() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_upper())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_word() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_word())
            {
                return false;
            }
        }

        return true;
    }

    bool string::is_xdigit() const
    {
        if (!m_length)
        {
            return false;
        }
        for (size_type i = 0; i < m_length; ++i)
        {
            if (!m_runes[m_offset + i].is_xdigit())
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
            const rune::value_type c = m_runes[m_offset + i].code();

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
        result.reserve(size);
        for (size_type i = 0; i < m_length; ++i)
        {
            const rune::value_type c = m_runes[m_offset + i].code();

            if (c > rune::max.code()
                || (c & 0xfffe) == 0xfffe
                || (c >= 0xd800 && c <= 0xdfff)
                || (c >= 0xffd0 && c <= 0xfdef))
            {
                continue;
            }
            else if (c < 0x80)
            {
                result << static_cast<char>(c);
            }
            else if (c < 0x800)
            {
                result << static_cast<char>(0xc0 | ((c & 0x7c0)) >> 6)
                       << static_cast<char>(0x80 | (c & 0x3f));
            }
            else if (c < 0x10000)
            {
                result << static_cast<char>(0xe0 | ((c & 0xf000) >> 12))
                       << static_cast<char>(0x80 | ((c & 0xfc0) >> 6))
                       << static_cast<char>(0x80 | (c & 0x3f));
            } else {
                result << static_cast<char>(0xf0 | ((c & 0x1c0000) >> 18))
                       << static_cast<char>(0x80 | ((c & 0x3f000) >> 12))
                       << static_cast<char>(0x80 | ((c & 0xfc0) >> 6))
                       << static_cast<char>(0x80 | (c & 0x3f));
            }
        }
        result << static_cast<char>(0);

        return result;
    }

    vector<char> string::utf16be() const
    {
        vector<char> result;
        size_type size = 0;

        for (size_type i = 0; i < m_length; ++i)
        {
            if (m_runes[m_offset + i] > 0xffff)
            {
                size += 4;
            } else {
                size += 2;
            }
        }
        result.reserve(size);
        for (size_type i = 0; i < m_length; ++i)
        {
            const rune::value_type c = m_runes[m_offset + i].code();

            if (c > 0xffff)
            {
                const rune::value_type plane = c >> 16;
                const rune::value_type high = (c & 0xff00) >> 8;

                result << static_cast<char>((plane >> 2) + 0xd8)
                       << static_cast<char>(((plane & 0x3) << 6) + (high >> 2))
                       << static_cast<char>((high & 0x2) + 0xdc)
                       << static_cast<char>(c & 0xff);
            } else {
                result << static_cast<char>((c & 0xff00) >> 8)
                       << static_cast<char>(c & 0xff);
            }
        }
        result << static_cast<char>(0);

        return result;
    }

    vector<char> string::utf16le() const
    {
        vector<char> result;
        size_type size = 0;

        for (size_type i = 0; i < m_length; ++i)
        {
            if (m_runes[m_offset + i] > 0xffff)
            {
                size += 4;
            } else {
                size += 2;
            }
        }
        result.reserve(size);
        for (size_type i = 0; i < m_length; ++i)
        {
            const rune::value_type c = m_runes[m_offset + i].code();

            if (c > 0xffff)
            {
                const rune::value_type plane = c >> 16;
                const rune::value_type high = (c & 0xff00) >> 8;

                result << static_cast<char>(((plane & 0x3) << 6) + (high >> 2))
                       << static_cast<char>((plane >> 2) + 0xd8)
                       << static_cast<char>(c & 0xff)
                       << static_cast<char>((high & 0x2) + 0xdc);
            } else {
                result << static_cast<char>(c & 0xff)
                       << static_cast<char>((c & 0xff00) >> 8);
            }
        }
        result << static_cast<char>(0);

        return result;
    }

    vector<char> string::utf32be() const
    {
        vector<char> result;

        result.reserve(m_length * 4);
        for (size_type i = 0; i < m_length; ++i)
        {
            const rune::value_type c = m_runes[m_offset + i].code();

            result << static_cast<char>((c & 0xff000000) >> 24)
                   << static_cast<char>((c & 0xff0000) >> 16)
                   << static_cast<char>((c & 0xff00) >> 8)
                   << static_cast<char>(c & 0xff);
        }
        result << static_cast<char>(0);

        return result;
    }

    vector<char> string::utf32le() const
    {
        vector<char> result;

        result.reserve(m_length * 4);
        for (size_type i = 0; i < m_length; ++i)
        {
            const rune::value_type c = m_runes[m_offset + i].code();

            result << static_cast<char>(c & 0xff)
                   << static_cast<char>((c & 0xff00) >> 8)
                   << static_cast<char>((c & 0xff0000) >> 16)
                   << static_cast<char>((c & 0xff000000) >> 24);
        }
        result << static_cast<char>(0);

        return result;
    }

    vector<wchar_t> string::widen() const
    {
        vector<wchar_t> result;
        size_type size = 0;

#if defined(_WIN32)
        for (size_type i = 0; i < m_length; ++i)
        {
            if (m_runes[m_offset + i] > 0xffff)
            {
                size += 2;
            } else {
                ++size;
            }
        }
#else
        for (size_type i = 0; i < m_length; ++i)
        {
            const rune::value_type c = m_runes[m_offset + i].code();

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
#endif
        result.reserve(size);
#if defined(_WIN32)
        for (size_type i = 0; i < m_length; ++i)
        {
            const rune::value_type c = m_runes[m_offset + i].code();

            if (c > 0xffff)
            {
                result << static_cast<wchar_t>(0xd800 + (c >> 10))
                       << static_cast<wchar_t>(0xdc00 + (c & 0x3ff));
            } else {
                result << static_cast<wchar_t>(c);
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

    string::size_type string::find(const string& str, size_type pos) const
    {
        if (!str.m_length || str.m_length > m_length)
        {
            return npos;
        }
        for (size_type i = pos; i < m_length; ++i)
        {
            bool found = true;

            if (i + str.m_length > m_length)
            {
                return npos;
            }
            for (size_type j = 0; j < str.m_length; ++j)
            {
                if (m_runes[m_offset + i + j] != str.m_runes[str.m_offset + j])
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                return i;
            }
        }

        return npos;
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

    string::size_type string::rfind(const string& str, size_type pos) const
    {
        if (pos == npos)
        {
            pos = m_length;
        }
        else if (pos > m_length || str.m_length > m_length)
        {
            return npos;
        }
        for (size_type i = m_length; i > 0; --i)
        {
            if (i > str.m_length)
            {
                bool found = true;

                for (size_type j = 0; j < str.m_length; ++j)
                {
                    if (m_runes[m_offset + i - str.m_length + j - 1] != str.m_runes[str.m_offset + j])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    return i - str.m_length - 1;
                }
            }
        }

        return npos;
    }

    string::size_type string::rfind(const_reference needle, size_type pos) const
    {
        if (pos == npos)
        {
            pos = m_length;
        }
        else if (pos > m_length)
        {
            return npos;
        }
        for (size_type i = pos; i > 0; --i)
        {
            if (m_runes[m_offset + i - 1] == needle)
            {
                return i - 1;
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

    vector<string> string::lines() const
    {
        vector<string> result;
        size_type begin = 0;
        size_type end = 0;

        for (size_type i = 0; i < m_length; ++i)
        {
            if (i + 1 < m_length
                && m_runes[m_offset + i] == '\r'
                && m_runes[m_offset + i + 1] == '\n')
            {
                result.push_back(substr(begin, end - begin));
                begin = end = i + 2;
                ++i;
            }
            else if (m_runes[m_offset + i] == '\n'
                    || m_runes[m_offset + i] == '\r')
            {
                result.push_back(substr(begin, end - begin));
                begin = end = i + 1;
            } else {
                ++end;
            }
        }
        if (end - begin > 0)
        {
            result.push_back(substr(begin, end - begin));
        }

        return result;
    }

    vector<string> string::words() const
    {
        vector<string> result;
        size_type begin = 0;
        size_type end = 0;

        for (size_type i = 0; i < m_length; ++i)
        {
            if (m_runes[m_offset + i].is_space())
            {
                if (end - begin > 0)
                {
                    result.push_back(substr(begin, end - begin));
                }
                begin = end = i + 1;
            } else {
                ++end;
            }
        }
        if (end - begin > 0)
        {
            result.push_back(substr(begin, end - begin));
        }

        return result;
    }

    string string::to_string(int n, int base)
    {
        stringbuilder sb;
        unsigned int magnitude;

        if (base < 2 || base > 36)
        {
            throw std::invalid_argument("base");
        }
        if (n == 0)
        {
            return "0";
        }
        magnitude = static_cast<unsigned int>(abs(n));
        do
        {
            sb.prepend(rune(digitmap[magnitude % base]));
            magnitude /= base;
        }
        while (magnitude != 0);
        if (n < 0)
        {
            sb.prepend(rune('-'));
        }

        return sb.str();
    }

    string string::to_string(unsigned int n, int base)
    {
        stringbuilder sb;

        if (base < 2 || base > 36)
        {
            throw std::invalid_argument("base");
        }
        if (n == 0)
        {
            return "0";
        }
        do
        {
            sb.prepend(rune(digitmap[n % base]));
            n /= base;
        }
        while (n != 0);

        return sb.str();
    }

    string string::to_string(long n, int base)
    {
        stringbuilder sb;
        unsigned long magnitude;

        if (base < 2 || base > 36)
        {
            throw std::invalid_argument("base");
        }
        if (n == 0)
        {
            return "0";
        }
        magnitude = static_cast<unsigned long>(abs(n));
        do
        {
            sb.prepend(rune(digitmap[magnitude % base]));
            magnitude /= base;
        }
        while (magnitude != 0);
        if (n < 0)
        {
            sb.prepend(rune('-'));
        }

        return sb.str();
    }

    string string::to_string(unsigned long n, int base)
    {
        stringbuilder sb;

        if (base < 2 || base > 36)
        {
            throw std::invalid_argument("base");
        }
        if (n == 0)
        {
            return "0";
        }
        do
        {
            sb.prepend(rune(digitmap[n % base]));
            n /= base;
        }
        while (n != 0);

        return sb.str();
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

    string::iterator::iterator()
        : m_pointer(0) {}

    string::iterator::iterator(const iterator& that)
        : m_pointer(that.m_pointer) {}

    string::iterator& string::iterator::operator=(const iterator& that)
    {
        m_pointer = that.m_pointer;

        return *this;
    }

    string::iterator& string::iterator::operator++()
    {
        ++m_pointer;

        return *this;
    }

    string::iterator string::iterator::operator++(int)
    {
        iterator tmp(*this);

        ++m_pointer;

        return tmp;
    }

    string::iterator& string::iterator::operator--()
    {
        --m_pointer;

        return *this;
    }

    string::iterator string::iterator::operator--(int)
    {
        iterator tmp(*this);

        --m_pointer;

        return tmp;
    }

    string::iterator string::iterator::operator+(size_type n) const
    {
        iterator result;

        result.m_pointer = m_pointer + n;

        return result;
    }

    string::iterator string::iterator::operator-(size_type n) const
    {
        iterator result;

        result.m_pointer = m_pointer - n;

        return *this;
    }

    string::iterator& string::iterator::operator+=(size_type n)
    {
        m_pointer += n;

        return *this;
    }

    string::iterator& string::iterator::operator-=(size_type n)
    {
        m_pointer -= n;

        return *this;
    }

    string::difference_type string::iterator::operator-(const iterator& that) const
    {
        return m_pointer - that.m_pointer;
    }
}
