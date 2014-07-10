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
#include <peelo/io/filename.hpp>
#if defined(_WIN32)
# include <windows.h>
#else
# include <unistd.h>
# include <sys/stat.h>
#endif

namespace peelo
{
#if defined(_WIN32)
    const rune filename::separator('\\');
#else
    const rune filename::separator('/');
#endif

    static void parse(const string&, string&, string&, vector<string>&);

    filename::filename() {}

    filename::filename(const filename& that)
        : m_filename(that.m_filename)
        , m_root(that.m_root)
        , m_path(that.m_path) {}

    filename::filename(const string& str)
    {
        parse(str, m_filename, m_root, m_path);
    }

    bool filename::is_separator(const rune& r)
    {
        return r == '/' || r == '\\';
    }

    bool filename::empty() const
    {
        return m_filename.empty();
    }

    filename& filename::assign(const filename& that)
    {
        m_filename.assign(that.m_filename);
        m_root.assign(that.m_root);
        m_path.assign(that.m_path);

        return *this;
    }

    filename& filename::assign(const string& str)
    {
        m_filename.clear();
        m_root.clear();
        m_path.clear();
        parse(str, m_filename, m_root, m_path);

        return *this;
    }

    bool filename::equals(const filename& that) const
    {
#if defined(_WIN32)
        return m_filename.equals_icase(that.m_filename);
#else
        return m_filename.equals(that.m_filename);
#endif
    }

    int filename::compare(const filename& that) const
    {
#if defined(_WIN32)
        return m_filename.compare_icase(that.m_filename);
#else
        return m_filename.compare(that.m_filename);
#endif
    }

    bool filename::is_absolute() const
    {
        return !m_root.empty();
    }

    bool filename::exists() const
    {
        if (empty())
        {
            return false;
        }
#if defined(_WIN32)
        return ::GetFileAttributesW(m_filename.widen().data())
            != INVALID_FILE_ATTRIBUTES;
#else
        return !::access(m_filename.utf8().data(), F_OK);
#endif
    }

    static void append(const string& input, vector<string>& path)
    {
        if (input.empty())
        {
            return;
        }
        else if (input[0] == '.')
        {
            if (input.length() == 2 && input[1] == '.')
            {
                if (!path.empty())
                {
                    path.erase(path.size() - 1);
                    return;
                }
            }
            else if (input.length() == 1)
            {
                if (!path.empty())
                {
                    return;
                }
            }
        }
        path.push_back(input);
    }

    static string compile(const string& root, const vector<string>& path)
    {
        vector<rune> result;

        if (!root.empty())
        {
            result.reserve(root.length());
            for (string::size_type i = 0; i < root.length(); ++i)
            {
                result.push_back(root[i]);
            }
        }
        for (vector<string>::size_type i = 0; i < path.size(); ++i)
        {
            if (i > 0 && !filename::is_separator(result[result.size() - 1]))
            {
                result.push_back(filename::separator);
            }
            result.reserve(result.size() + path[i].length());
            for (string::size_type j = 0; j < path[i].length(); ++j)
            {
                result.push_back(path[i][j]);
            }
        }

        return string(result.data(), result.size());
    }

    static void parse(const string& source,
                      string& filename,
                      string& root,
                      vector<string>& path)
    {
        string::size_type begin = 0;
        string::size_type end = 0;

        if (source.empty())
        {
            return;
        }
        else if (filename::is_separator(source[0]))
        {
            root.assign(source.substr(0, 1));
            if (source.length() == 1)
            {
                filename.assign(root);
                return;
            }
            begin = 1;
        }
#if defined(_WIN32)
        else if (source.length() > 1
                && source[0].is_alpha()
                && source[1] == ':')
        {
            if (source.length() == 2)
            {
                root.assign(source);
                filename.assign(root);
                return;
            }
            else if (filename::is_separator(source[2]))
            {
                root.assign(source.substr(0, 2));
                begin = 3;
            }
        }
#endif
        for (string::size_type i = begin; i < source.length(); ++i)
        {
            if (filename::is_separator(source[i]))
            {
                if (end)
                {
                    append(source.substr(begin, end), path);
                }
                begin = i + 1;
                end = 0;
            } else {
                ++end;
            }
        }
        if (end)
        {
            append(source.substr(begin, end), path);
        }
        filename.assign(compile(root, path));
    }
}
