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
#ifndef PEELO_CONTAINER_RANGE_HPP_GUARD
#define PEELO_CONTAINER_RANGE_HPP_GUARD

#include <iostream>

namespace peelo
{
    template <class T>
    class range
    {
    public:
        typedef T value_type;
        
        class iterator
        {
            friend class range;

        public:
            iterator(const iterator& that)
                : m_current(that.m_current) {}

            iterator& operator=(const iterator& that)
            {
                m_current = that.m_current;

                return *this;
            }
        
            inline value_type operator*() const
            {
                return m_current;
            }

            inline iterator& operator++()
            {
                ++m_current;

                return *this;
            }

            inline iterator operator++(int)
            {
                iterator copy(*this);

                ++m_current;

                return copy;
            }

            inline iterator& operator--()
            {
                --m_current;

                return *this;
            }

            inline iterator operator--(int)
            {
                iterator copy(*this);

                --m_current;

                return copy;
            }

            inline bool operator==(const iterator& that) const
            {
                return m_current == that.m_current;
            }

            inline bool operator!=(const iterator& that) const
            {
                return !(m_current == that.m_current);
            }

        protected:
            iterator(const value_type& start)
                : m_current(start) {}

        private:
            value_type m_current;
        };

        range()
            : m_front(T())
            , m_back(T()) {}

        range(const range<T>& that)
            : m_front(that.m_front)
            , m_back(that.m_back) {}

        range(const value_type& front, const value_type& back)
            : m_front(front)
            , m_back(back) {}

        inline const value_type& front() const
        {
            return m_front;
        }

        inline const value_type& back() const
        {
            return m_back;
        }

        inline iterator begin() const
        {
            return iterator(m_front);
        }

        inline iterator end() const
        {
            return iterator(m_back);
        }

    private:
        value_type m_front;
        value_type m_back;
    };

    template <class T>
    std::ostream& operator<<(std::ostream& os, const range<T>& r)
    {
        os << r.front() << "..." << r.back();
    }
}

#endif /* !PEELO_CONTAINER_RANGE_HPP_GUARD */
