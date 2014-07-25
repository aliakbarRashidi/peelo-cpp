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
#include <peelo/io/filepath.hpp>

namespace peelo
{
    static void parse(const string&, set<filename>&);

#if defined(_WIN32)
    const rune filepath::separator(';');
#else
    const rune filepath::separator(':');
#endif

    filepath::filepath() {}

    filepath::filepath(const filepath& that)
        : m_filenames(that.m_filenames) {}

    filepath::filepath(const set<filename>& filenames)
        : m_filenames(filenames) {}

    filepath::filepath(const string& str)
    {
        parse(str, m_filenames);
    }

    bool filepath::is_separator(const rune& r)
    {
        return r == ':' || r == ';';
    }

    filepath& filepath::assign(const filepath& that)
    {
        m_filenames = that.m_filenames;

        return *this;
    }

    filepath& filepath::assign(const set<filename>& filenames)
    {
        m_filenames = filenames;

        return *this;
    }

    filepath& filepath::assign(const string& str)
    {
        m_filenames.clear();
        parse(str, m_filenames);

        return *this;
    }

    bool filepath::equals(const filepath& that) const
    {
        return m_filenames == that.m_filenames;
    }

    static void parse(const string& source, set<filename>& filenames)
    {
        string::size_type begin = 0;
        string::size_type end = 0;

        if (source.empty())
        {
            return;
        }
        for (string::size_type i = 0; i < source.length(); ++i)
        {
            if (source[i] == filepath::separator)
            {
                if (end - begin > 0)
                {
                    string str = source.substr(begin, end - begin);

                    if (!str.empty() && !str.is_space())
                    {
                        filenames.insert(str);
                    }
                }
                begin = end = i + 1;
            } else {
                ++end;
            }
        }
        if (end - begin > 0)
        {
            string str = source.substr(begin, end - begin);

            if (!str.empty() && !str.is_space())
            {
                filenames.insert(str);
            }
        }
    }

    std::ostream& operator<<(std::ostream& os, const class filepath& filepath)
    {
        const set<filename>& filenames = filepath.filenames();

        for (set<filename>::const_iterator i = filenames.begin();
             i != filenames.end();
             ++i)
        {
            if (i != filenames.begin())
            {
                os << filepath::separator;
            }
            os << *i;
        }

        return os;
    }

    std::wostream& operator<<(std::wostream& os, const class filepath& filepath)
    {
        const set<filename>& filenames = filepath.filenames();

        for (set<filename>::const_iterator i = filenames.begin();
             i != filenames.end();
             ++i)
        {
            if (i != filenames.begin())
            {
                os << filepath::separator;
            }
            os << *i;
        }

        return os;
    }
}
