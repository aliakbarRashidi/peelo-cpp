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
#ifndef PEELO_CONTAINER_PAIR_HPP_GUARD
#define PEELO_CONTAINER_PAIR_HPP_GUARD

#include <iostream>

namespace peelo
{
    template <class T1, class T2>
    class pair
    {
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        pair()
            : m_first(T1())
            , m_second(T2()) {}

        pair(const pair<T1, T2>& that)
            : m_first(that.m_first)
            , m_second(that.m_second) {}

        pair(const T1& first, const T2& second)
            : m_first(first)
            , m_second(second) {}

        inline T1& first()
        {
            return m_first;
        }

        inline const T1& first() const
        {
            return m_first;
        }

        inline T2& second()
        {
            return m_second;
        }

        inline const T2& second() const
        {
            return m_second;
        }

        pair& assign(const pair<T1, T2>& that)
        {
            m_first = that.m_first;
            m_second = that.m_second;

            return *this;
        }

        pair& assign(const T1& first, const T2& second)
        {
            m_first = first;
            m_second = m_second;

            return *this;
        }

        inline pair& operator=(const pair<T1, T2>& that)
        {
            return assign(that);
        }

        bool equals(const pair<T1, T2>& that) const
        {
            return m_first == that.m_first && m_second == that.m_second;
        }

        inline bool operator==(const pair<T1, T2>& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const pair<T1, T2>& that) const
        {
            return !equals(that);
        }

    private:
        T1 m_first;
        T2 m_second;
    };

    template <class T1, class T2>
    inline pair<T1, T2> make_pair(const T1& first, const T2& second)
    {
        return pair<T1, T2>(first, second);
    }

    template <class T1, class T2>
    inline std::ostream& operator<<(std::ostream& os, const pair<T1, T2>& p)
    {
        os << p.first() << p.second();

        return os;
    }
}

#endif /* !PEELO_CONTAINER_PAIR_HPP_GUARD */
