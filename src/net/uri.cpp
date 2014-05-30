#include <peelo/net/uri.hpp>

namespace peelo
{
    uri::uri(const string& scheme,
             const string& username,
             const string& password,
             const string& hostname,
             int port,
             const string& path,
             const string& query,
             const string& fragment)
        : m_scheme(scheme)
        , m_username(username)
        , m_password(password)
        , m_hostname(hostname)
        , m_port(port)
        , m_path(path)
        , m_query(query)
        , m_fragment(fragment) {}

    uri::uri(const uri& that)
        : m_scheme(that.m_scheme)
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
        m_username.assign(that.m_username);
        m_password.assign(that.m_password);
        m_hostname.assign(that.m_hostname);
        m_port = that.m_port;
        m_path.assign(that.m_path);
        m_query.assign(that.m_query);
        m_fragment.assign(that.m_fragment);

        return *this;
    }
}
