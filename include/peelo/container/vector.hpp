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
#ifndef PEELO_CONTAINER_VECTOR_HPP_GUARD
#define PEELO_CONTAINER_VECTOR_HPP_GUARD

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace peelo
{
    /**
     * Vector is a template class for dynamic array.
     */
    template <class T>
    class vector
    {
    public:
        typedef std::size_t size_type;
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;

        /**
         * Constructs empty vector.
         */
        vector()
            : m_capacity(0)
            , m_size(0)
            , m_data(NULL) {}

        /**
         * Copy constructor.
         */
        vector(const vector<T>& that)
            : m_capacity(that.m_size)
            , m_size(that.m_size)
            , m_data(m_capacity ? static_cast<T*>(std::malloc(sizeof(T) * m_capacity)) : NULL)
        {
            for (size_type i = 0; i < m_size; ++i)
            {
                new (static_cast<void*>(m_data + i)) T(that.m_data[i]);
            }
        }

        explicit vector(size_type count, const_reference value)
            : m_capacity(count)
            , m_size(count)
            , m_data(m_capacity ? static_cast<T*>(std::malloc(sizeof(T) * m_capacity)) : NULL)
        {
            for (size_type i = 0; i < count; ++i)
            {
                new (static_cast<void*>(m_data + i)) T(value);
            }
        }

        /**
         * Destructor.
         */
        virtual ~vector()
        {
            for (size_type i = 0; i < m_size; ++i)
            {
                m_data[i].~T();
            }
            if (m_size)
            {
                std::free(static_cast<void*>(m_data));
            }
        }

        inline operator bool() const
        {
            return m_size;
        }

        inline bool operator!() const
        {
            return !m_size;
        }

        /**
         * Returns a reference to the element at specified location pos, with
         * bounds checking.
         *
         * If pos not within the range of the container, an exception of type
         * std::out_of_range is thrown.
         */
        inline reference at(size_type pos)
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("vector index out of bounds");
            } else {
                return m_data[pos];
            }
        }

        inline const_reference at(size_type pos) const
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("vector index out of bounds");
            } else {
                return m_data[pos];
            }
        }

        /**
         * Returns a reference to the element at specified location pos. No
         * bounds checking is performed.
         */
        inline reference operator[](size_type pos)
        {
            return m_data[pos];
        }

        inline const_reference operator[](size_type pos) const
        {
            return m_data[pos];
        }

        /**
         * Returns a reference to the first element in the container.
         *
         * Calling front on an empty container is undefined.
         */
        inline reference front()
        {
            return m_data[0];
        }

        inline const_reference front() const
        {
            return m_data[0];
        }

        /**
         * Returns reference to the last element in the container.
         *
         * Calling back on an empty container is undefined.
         */
        inline reference back()
        {
            return m_data[m_size - 1];
        }

        inline const_reference back() const
        {
            return m_data[m_size - 1];
        }

        /**
         * Returns pointer to the underlying array serving as element storage.
         * The returned pointer could be NULL if the vector is empty.
         */
        inline pointer data()
        {
            return m_data;
        }

        inline const_pointer data() const
        {
            return m_data;
        }

        /**
         * Returns <code>true</code> if the vector is empty.
         */
        inline bool empty() const
        {
            return !m_size;
        }

        inline size_type size() const
        {
            return m_size;
        }

        /**
         * Ensures that the vector has capacity for at least <i>n</i> elements.
         */
        void reserve(size_type n)
        {
            pointer old;

            if (m_capacity >= n)
            {
                return;
            }
            old = m_data;
            m_capacity = n;
            m_data = static_cast<T*>(std::malloc(sizeof(T) * m_capacity));
            for (size_type i = 0; i < m_size; ++i)
            {
                new (static_cast<void*>(m_data + i)) T(old[i]);
                old[i].~T();
            }
            if (old)
            {
                std::free(static_cast<void*>(old));
            }
        }

        inline size_type capacity() const
        {
            return m_capacity;
        }

        void clear()
        {
            for (size_type i = 0; i < m_size; ++i)
            {
                m_data[i].~T();
            }
            m_size = 0;
        }

        /**
         * Inserts <i>value</i> at index position <i>i</i> in the vector. If
         * <i>i</i> is <code>0</code>, then value is prepended to the vector.
         * If <i>i</i> is size(), then value is appended to the vector.
         */
        void insert(size_type i, const_reference value)
        {
            if (i > m_size)
            {
                throw std::out_of_range("vector index out of range");
            }
            else if (!i)
            {
                push_front(value);
            }
            else if (i == m_size)
            {
                push_back(value);
            } else {
                if (m_capacity >= m_size + 1)
                {
                    std::memmove(
                            static_cast<void*>(m_data + i + 1),
                            static_cast<const void*>(m_data + i),
                            sizeof(T) * (m_size - i)
                    );
                } else {
                    pointer old = m_data;

                    m_data = static_cast<T*>(std::malloc(sizeof(T) * (m_size + 1)));
                    for (size_type j = 0; j < i - 1; ++j)
                    {
                        new (static_cast<void*>(m_data + j)) T(old[j]);
                        old[j].~T();
                    }
                    for (size_type j = i; j < m_size; ++j)
                    {
                        new (static_cast<void*>(m_data + j + 1)) T(old[j]);
                        old[j].~T();
                    }
                    if (old)
                    {
                        std::free(static_cast<void*>(old));
                    }
                }
                new (static_cast<void*>(m_data + i)) T(value);
                ++m_size;
            }
        }

        void erase(size_type pos)
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("vector index out of bounds");
            }
            m_data[pos].~T();
            std::memmove(
                    static_cast<void*>(m_data + pos),
                    static_cast<const void*>(m_data + pos + 1),
                    sizeof(T) * (--m_size - pos)
            );
        }

        void push_back(const_reference value)
        {
            reserve(m_size + 1);
            new (static_cast<void*>(m_data + m_size++)) T(value);
        }

        void push_front(const_reference value)
        {
            if (m_capacity >= m_size + 1)
            {
                std::memmove(
                        static_cast<void*>(m_data + 1),
                        static_cast<const void*>(m_data),
                        sizeof(T) * m_size
                );
            } else {
                ++m_capacity;
                if (m_size)
                {
                    pointer old = m_data;

                    m_data = static_cast<T*>(std::malloc(sizeof(T) * m_capacity));
                    for (size_type i = 0; i < m_size; ++i)
                    {
                        new (static_cast<void*>(m_data + i + 1)) T(old[i]);
                        old[i].~T();
                    }
                    if (old)
                    {
                        std::free(static_cast<void*>(old));
                    }
                } else {
                    if (m_data)
                    {
                        std::free(static_cast<void*>(m_data));
                    }
                    m_data = static_cast<T*>(std::malloc(sizeof(T) * m_capacity));
                }
            }
            new (static_cast<void*>(m_data)) T(value);
            ++m_size;
        }

        inline vector& operator<<(const_reference value)
        {
            push_back(value);

            return *this;
        }

        /**
         * Returns and removes last element from the vector.
         */
        value_type pop_back()
        {
            if (m_size)
            {
                value_type element(m_data[--m_size]);

                m_data[m_size].~T();

                return element;
            }

            throw std::out_of_range("vector is empty");
        }

        /**
         * Returns and removes first element from the vector.
         */
        value_type pop_front()
        {
            if (m_size)
            {
                value_type element(m_data[0]);

                m_data[0].~T();
                std::memmove(
                        static_cast<void*>(m_data),
                        static_cast<const void*>(m_data + 1),
                        sizeof(T) * --m_size
                );
            }

            throw std::out_of_range("vector is empty");
        }

        inline vector& operator>>(reference value)
        {
            value = pop_back();

            return *this;
        }

        void swap(vector<T>& that)
        {
            if (m_data != that.m_data)
            {
                pointer tmp = m_data;

                m_data = that.m_data;
                that.m_data = tmp;
            }
        }

        bool equals(const vector<T>& that) const
        {
            if (m_data == that.m_data)
            {
                return true;
            }
            else if (m_size != that.m_size)
            {
                return false;
            }
            for (size_type i = 0; i < m_size; ++i)
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
        inline bool operator==(const vector<T>& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const vector<T>& that) const
        {
            return !equals(that);
        }

        int compare(const vector<T>& that) const
        {
            size_type n;

            if (m_data == that.m_data)
            {
                return 0;
            }
            n = m_size > that.m_size ? that.m_size : m_size;
            for (size_type i = 0; i < n; ++i)
            {
                const_reference a = m_data[i];
                const_reference b = that.m_data[i];

                if (!(a == b))
                {
                    return a < b ? -1 : 1;
                }
            }

            return m_size > that.m_size ? 1 : m_size < that.m_size ? -1 : 0;
        }

        inline bool operator<(const vector<T>& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const vector<T>& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const vector<T>& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const vector<T>& that) const
        {
            return compare(that) >= 0;
        }

        vector& assign(const vector<T>& that)
        {
            if (m_data != that.m_data)
            {
                for (size_type i = 0; i < m_size; ++i)
                {
                    m_data[i].~T();
                }
                if (m_capacity < that.m_size)
                {
                    m_capacity = that.m_size;
                    if (m_data)
                    {
                        std::free(static_cast<void*>(m_data));
                    }
                    m_data = static_cast<T*>(std::malloc(sizeof(T) * m_capacity));
                }
                m_size = that.m_size;
                for (size_type i = 0; i < m_size; ++i)
                {
                    new (static_cast<void*>(m_data + i)) T(that.m_data[i]);
                }
            }

            return *this;
        }

        /**
         * Assignment operator.
         */
        inline vector& operator=(const vector<T>& that)
        {
            return assign(that);
        }

    private:
        /** Size of the array. */
        size_type m_capacity;
        /** Number of elements stored in the array. */
        size_type m_size;
        /** Pointer to the array data. */
        pointer m_data;
    };

    template <class T>
    inline std::ostream& operator<<(std::ostream& os, const vector<T>& v)
    {
        for (std::size_t i = 0; i < v.size(); ++i)
        {
            if (i > 0)
            {
                os << ", ";
            }
            os << v[i];
        }

        return os;
    }
}

#endif /* !PEELO_CONTAINER_VECTOR_HPP_GUARD */
