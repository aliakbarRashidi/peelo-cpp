#include <peelo/number/ratio.hpp>

namespace peelo
{
    static inline int64_t gcd(int64_t a, int64_t b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    ratio::ratio()
        : m_numerator(0)
        , m_denominator(0) {}

    ratio::ratio(const ratio& that)
        : m_numerator(that.m_numerator)
        , m_denominator(that.m_denominator) {}

    ratio::ratio(int64_t numerator, int64_t denominator)
        throw(std::domain_error)
        : m_numerator(0)
        , m_denominator(0)
    {
        if (denominator == 0)
        {
            throw std::domain_error("division by zero");
        }

        const int64_t g = gcd(numerator, denominator);

        m_numerator = numerator / g;
        m_denominator = denominator / g;
    }

    ratio& ratio::assign(const ratio& that)
    {
        m_numerator = that.m_numerator;
        m_denominator = that.m_denominator;

        return *this;
    }

    bool ratio::equals(const ratio& that) const
    {
        return m_numerator == that.m_numerator
            && m_denominator == that.m_denominator;
    }

    int ratio::compare(const ratio& that) const
    {
        const int64_t a = m_numerator * that.m_numerator;
        const int64_t b = m_denominator * that.m_denominator;

        return a < b ? -1 : a > b ? 1 : 0;
    }

    ratio ratio::operator-() const
    {
        return ratio(-m_numerator, m_denominator);
    }

    ratio ratio::operator+(const ratio& that) const
    {
        return ratio(
                m_numerator * that.m_numerator + m_denominator * that.m_denominator,
                m_denominator * that.m_denominator
        );
    }

    ratio ratio::operator+(int64_t n) const
    {
        return operator+(ratio(n));
    }

    ratio ratio::operator-(const ratio& that) const
    {
        return ratio(
                m_numerator * that.m_numerator - m_denominator * that.m_denominator,
                m_denominator * that.m_denominator
        );
    }

    ratio ratio::operator-(int64_t n) const
    {
        return operator-(ratio(n));
    }

    ratio ratio::operator*(const ratio& that) const
    {
        return ratio(
                m_numerator * that.m_numerator,
                m_denominator * that.m_denominator
        );
    }

    ratio ratio::operator*(int64_t n) const
    {
        return operator*(ratio(n));
    }

    ratio ratio::operator/(const ratio& that) const
    {
        return ratio(
                m_numerator * that.m_denominator,
                m_denominator * that.m_numerator
        );
    }

    std::ostream& operator<<(std::ostream& os, const class ratio& ratio)
    {
        os << ratio.numerator() << '/' << ratio.denominator();

        return os;
    }
}
