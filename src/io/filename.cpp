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
    filename::filename() {}

    filename::filename(const filename& that)
        : m_path(that.m_path)
        , m_device(that.m_device)
        , m_location(that.m_location)
        , m_file(that.m_file)
        , m_extension(that.m_extension) {}

    bool filename::is_separator(const rune& r)
    {
        return r == '/' || r == '\\';
    }

    bool filename::empty() const
    {
        return m_path.empty();
    }

    filename& filename::assign(const filename& that)
    {
        m_path = that.m_path;
        m_device = that.m_device;
        m_location = that.m_location;
        m_file = that.m_file;
        m_extension = that.m_extension;

        return *this;
    }

    bool filename::equals(const filename& that) const
    {
        return m_path == that.m_path;
    }

    int filename::compare(const filename& that) const
    {
#if defined(_WIN32)
        return m_path.compare_icase(that.m_path);
#else
        return m_path.compare(that.m_path);
#endif
    }

    bool filename::is_absolute() const
    {
        return !m_location.empty() && is_separator(m_location[0]);
    }

    bool filename::exists() const
    {
        if (empty())
        {
            return false;
        }
#if defined(_WIN32)
        return ::GetFileAttributesW(m_path.widen().data())
            != INVALID_FILE_ATTRIBUTES;
#else
        return !::access(m_path.utf8().data(), F_OK);
#endif
    }
}
