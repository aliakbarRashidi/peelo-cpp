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

        if (scheme)
        {
            const string& scheme_specific = uri.scheme_specific();

            os << scheme << ':';
            if (scheme_specific)
            {
                os << scheme_specific;
            }
        }
        if (hostname)
        {
            const string& username = uri.username();
            const string& password = uri.password();
            int port = uri.port();

            if (username && password)
            {
                os << username << ':' << password << '@';
            }
            os << hostname;
            if (port >= 0)
            {
                os << ':' << port;
            }
            if (path && !path[0].equals('/'))
            {
                os << '/';
            }
        }
        if (path)
        {
            os << path;
        }
        if (query)
        {
            os << '?' << query;
        }
        if (fragment)
        {
            os << '#' << fragment;
        }

        return os;
    }
}
