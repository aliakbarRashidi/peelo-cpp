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
#ifndef PEELO_NET_URI_HPP_GUARD
#define PEELO_NET_URI_HPP_GUARD

#include <peelo/text/string.hpp>

namespace peelo
{
    class uri
    {
    public:
        /**
         * Default constructor for URI.
         */
        explicit uri(const string& scheme = string(),
                     const string& scheme_specific = string(),
                     const string& username = string(),
                     const string& password = string(),
                     const string& hostname = string(),
                     int port = 0,
                     const string& path = string(),
                     const string& query = string(),
                     const string& fragment = string());

        /**
         * Copy constructor.
         *
         * \param that Other URI to construct copy of
         */
        uri(const uri& that);

        /**
         * Returns scheme of the URI or empty string if not specified.
         */
        inline const string& scheme() const
        {
            return m_scheme;
        }

        /**
         * Returns scheme specific information or empty string if not
         * specified.
         */
        inline const string& scheme_specific() const
        {
            return m_scheme_specific;
        }

        /**
         * Returns the authority part of the URI in form of
         * "username:password", or empty string if it's not defined in the
         * URI.
         */
        string authority() const;

        /**
         * Returns username part of the authority, or empty string if it's not
         * specified.
         */
        inline const string& username() const
        {
            return m_username;
        }

        /**
         * Returns password part of the authority, or empty string if it's not
         * specified.
         */
        inline const string& password() const
        {
            return m_password;
        }

        /**
         * Returns hostname part of the URI, or empty string if it's not
         * specified.
         */
        inline const string& hostname() const
        {
            return m_hostname;
        }

        /**
         * Returns port number, or 0 if it's not specified in the URI.
         */
        inline int port() const
        {
            return m_port;
        }

        /**
         * Returns path of the URI, or empty string if it's not specified.
         */
        inline const string& path() const
        {
            return m_path;
        }

        /**
         * Returns query string of the URI, or empty string if it's not
         * specified.
         */
        inline const string& query() const
        {
            return m_query;
        }

        /**
         * Returns fragment part of the URI, or empty string if it's not
         * specified.
         */
        inline const string& fragment() const
        {
            return m_fragment;
        }

        /**
         * Copies contents of another URI into this one.
         *
         * \param that Other URI to copy content from
         */
        uri& assign(const uri& that);

        /**
         * Assignment operator.
         */
        inline uri& operator=(const uri& that)
        {
            return assign(that);
        }

    private:
        string m_scheme;
        string m_scheme_specific;
        string m_username;
        string m_password;
        string m_hostname;
        int m_port;
        string m_path;
        string m_query;
        string m_fragment;
    };

    std::ostream& operator<<(std::ostream&, const uri&);
}

#endif /* !PEELO_NET_URI_HPP_GUARD */
