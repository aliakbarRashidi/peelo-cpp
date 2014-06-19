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
#include <peelo/net/uri.hpp>

namespace peelo
{
    uri::uri(const string& scheme,
             const string& scheme_specific,
             const string& username,
             const string& password,
             const string& hostname,
             int port,
             const string& path,
             const string& query,
             const string& fragment)
        : m_scheme(scheme)
        , m_scheme_specific(scheme_specific)
        , m_username(username)
        , m_password(password)
        , m_hostname(hostname)
        , m_port(port)
        , m_path(path)
        , m_query(query)
        , m_fragment(fragment) {}

    uri::uri(const uri& that)
        : m_scheme(that.m_scheme)
        , m_scheme_specific(that.m_scheme_specific)
        , m_username(that.m_username)
        , m_password(that.m_password)
        , m_hostname(that.m_hostname)
        , m_port(that.m_port)
        , m_path(that.m_path)
        , m_query(that.m_query)
        , m_fragment(that.m_fragment) {}

    string uri::authority() const
    {
        if (m_username.empty() && m_password.empty())
        {
            return string();
        } else {
            return m_username + rune(':') + m_password;
        }
    }

    uri& uri::assign(const uri& that)
    {
        m_scheme.assign(that.m_scheme);
        m_scheme_specific.assign(that.m_scheme_specific);
        m_username.assign(that.m_username);
        m_password.assign(that.m_password);
        m_hostname.assign(that.m_hostname);
        m_port = that.m_port;
        m_path.assign(that.m_path);
        m_query.assign(that.m_query);
        m_fragment.assign(that.m_fragment);

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const class uri& uri)
    {
        const string& scheme = uri.scheme();
        const string& hostname = uri.hostname();
        const string& path = uri.path();
        const string& query = uri.query();
        const string& fragment = uri.fragment();

        if (!scheme.empty())
        {
            const string& scheme_specific = uri.scheme_specific();

            os << scheme << ':';
            if (!scheme_specific.empty())
            {
                os << scheme_specific;
            }
        }
        if (!hostname.empty())
        {
            const string& username = uri.username();
            const string& password = uri.password();
            int port = uri.port();

            if (!username.empty() && !password.empty())
            {
                os << username << ':' << password << '@';
            }
            os << hostname;
            if (port >= 0)
            {
                os << ':' << port;
            }
            if (!path.empty() && path[0] == '/')
            {
                os << '/';
            }
        }
        if (!path.empty())
        {
            os << path;
        }
        if (!query.empty())
        {
            os << '?' << query;
        }
        if (!fragment.empty())
        {
            os << '#' << fragment;
        }

        return os;
    }
}
