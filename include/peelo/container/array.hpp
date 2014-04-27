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
#ifndef PEELO_CONTAINER_ARRAY_HPP_GUARD
#define PEELO_CONTAINER_ARRAY_HPP_GUARD

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace peelo
{
    template <class T, std::size_t N>
    class array
    {
    public:
        typedef std::size_t size_type;
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;

        array()
            : m_data(N ? static_cast<T*>(std::malloc(sizeof(T) * N)) : NULL)
        {
            for (size_type i = 0; i < N; ++i)
            {
                new (static_cast<void*>(m_data + i)) T();
            }
        }

        /**
         * Copy constructor.
         */
        array(const array<T, N>& that)
            : m_data(N ? static_cast<T*>(std::malloc(sizeof(T) * N)) : NULL)
        {
            for (size_type i = 0; i < N; ++i)
            {
                new (static_cast<void*>(m_data + i)) T(that.m_data[i]);
            }
        }

        /**
         * Destructor.
         */
        virtual ~array()
        {
            for (size_type i = 0; i < N; ++i)
            {
                m_data[i].~T();
            }
            if (N)
            {
                std::free(static_cast<void*>(m_data));
            }
        }

        inline operator bool() const
        {
            return N;
        }

        inline bool operator!() const
        {
            return !N;
        }

        inline reference at(size_type pos)
        {
            if (pos >= N)
            {
                throw std::out_of_range("array index out of bounds");
            } else {
                return m_data[pos];
            }
        }

        inline const_reference at(size_type pos) const
        {
            if (pos >= N)
            {
                throw std::out_of_range("array index out of bounds");
            } else {
                return m_data[pos];
            }
        }

        inline reference operator[](size_type pos)
        {
            return m_data[pos];
        }

        inline const_reference operator[](size_type pos) const
        {
            return m_data[pos];
        }

        /**
         * Returns a reference to the first element in the container. Calling
         * front() on an empty container is undefined.
         */
        inline reference front()
        {
            return m_data[0];
        }

        inline const_reference front() const
        {
            return m_data[0];
        }

        inline reference back()
        {
            return m_data[N - 1];
        }

        inline const_reference back() const
        {
            return m_data[N - 1];
        }

        inline pointer data()
        {
            return m_data;
        }

        inline const_pointer data() const
        {
            return m_data;
        }

        /**
         * Returns <code>true</code> if the array is empty.
         */
        inline bool empty() const
        {
            return !N;
        }

        inline size_type size() const
        {
            return N;
        }

        /**
         * Assigns the given value to all elements in the container.
         */
        void fill(const_reference value)
        {
            for (size_type i = 0; i < N; ++i)
            {
                m_data[i] = value;
            }
        }

        void swap(array<T, N>& that)
        {
            pointer tmp = m_data;

            m_data = that.m_data;
            that.m_data = tmp;
        }

        array& assign(const array<T, N>& that)
        {
            if (m_data != that.m_data)
            {
                for (size_type i = 0; i < N; ++i)
                {
                    m_data[i] = that.m_data[i];
                }
            }

            return *this;
        }

        /**
         * Assignment operator.
         */
        inline array& operator=(const array<T, N>& that)
        {
            return assign(that);
        }

        bool equals(const array<T, N>& that) const
        {
            if (m_data == that.m_data)
            {
                return true;
            }
            for (size_type i = 0; i < N; ++i)
            {
                if (!(m_data[i] == that.m_data[i]))
                {
                    return false;
                }
            }

            return true;
        }

        /**
         * Equality testing operator.
         */
        inline bool operator==(const array<T, N>& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const array<T, N>& that) const
        {
            return !equals(that);
        }

        int compare(const array<T, N>& that) const
        {
            if (m_data == that.m_data)
            {
                return 0;
            }
            for (size_type i = 0; i < N; ++i)
            {
                const_reference a = m_data[i];
                const_reference b = that.m_data[i];

                if (!(a == b))
                {
                    return a < b ? -1 : 1;
                }
            }

            return 0;
        }

        inline bool operator<(const array<T, N>& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const array<T, N>& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const array<T, N>& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const array<T, N>& that) const
        {
            return compare(that) >= 0;
        }

    private:
        pointer m_data;
    };

    template <class T, std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, const array<T, N>& a)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            if (i > 0)
            {
                os << ", ";
            }
            os << a[i];
        }

        return os;
    }
}

#endif /* !PEELO_CONTAINER_ARRAY_HPP_GUARD */