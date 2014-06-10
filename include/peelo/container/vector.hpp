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

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace peelo
{
    /**
     * Vector is a template class for dynamic array.
     */
    template <
        class T,
        class Allocator = std::allocator<T>
    >
    class vector
    {
    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;

        /**
         * Constructs empty vector.
         *
         * \param allocator Allocator used for allocating memory
         */
        vector(const allocator_type& allocator = allocator_type())
            : m_allocator(allocator)
            , m_capacity(0)
            , m_size(0)
            , m_data(0) {}

        /**
         * Copy constructor.
         */
        vector(const vector<T>& that)
            : m_allocator(that.m_allocator)
            , m_capacity(that.m_size)
            , m_size(m_capacity)
            , m_data(m_size ? m_allocator.allocate(m_size) : 0)
        {
            for (size_type i = 0; i < m_size; ++i)
            {
                m_allocator.construct(m_data + i, that.m_data[i]);
            }
        }

        /**
         * Constructs vector which contains <i>count</i> instances of given
         * value.
         *
         * \param count Number of instances of the given <i>value</i> to store
         *              in the vector
         * \param value The value to store in the vector
         * \param allocator Allocator used for allocating memory
         */
        explicit vector(size_type count,
                        const_reference value,
                        const allocator_type& allocator = allocator_type())
            : m_allocator(allocator)
            , m_capacity(count)
            , m_size(count)
            , m_data(m_size ? m_allocator.allocate(m_size) : 0)
        {
            for (size_type i = 0; i < m_size; ++i)
            {
                m_allocator.construct(m_data + i, value);
            }
        }

        /**
         * Destructor.
         */
        virtual ~vector()
        {
            for (size_type i = 0; i < m_size; ++i)
            {
                m_allocator.destroy(m_data + i);
            }
            if (m_data)
            {
                m_allocator.deallocate(m_data, m_capacity);
            }
        }

        /**
         * Returns <code>true</code> if the vector is not empty.
         */
        inline operator bool() const
        {
            return m_size;
        }

        /**
         * Returns <code>true</code> if the vector is empty.
         */
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
         *
         * \throw std::out_of_range If index is out of bounds.
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
            m_data = m_allocator.allocate(n);
            for (size_type i = 0; i < m_size; ++i)
            {
                m_allocator.construct(m_data + i, old[i]);
                m_allocator.destroy(old + i);
            }
            if (old)
            {
                m_allocator.deallocate(old, m_capacity);
            }
            m_capacity = n;
        }

        /**
         * Returns current capacity of the vector.
         */
        inline size_type capacity() const
        {
            return m_capacity;
        }

        /**
         * Removes all elements from the vector.
         */
        void clear()
        {
            for (size_type i = 0; i < m_size; ++i)
            {
                m_allocator.destroy(m_data + i);
            }
            m_size = 0;
        }

        /**
         * Inserts <i>value</i> at index position <i>i</i> in the vector. If
         * <i>i</i> is <code>0</code>, then value is prepended to the vector.
         * If <i>i</i> is size(), then value is appended to the vector.
         *
         * \throw std::out_of_range If index is out of bounds.
         */
        void insert(size_type i, const_reference value)
        {
            if (i >= m_size)
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
                            sizeof(value_type) * (m_size - i)
                    );
                } else {
                    pointer old = m_data;

                    m_data = m_allocator.allocate(m_size + 1);
                    for (size_type j = 0; j < i - 1; ++j)
                    {
                        m_allocator.construct(m_data + j, old[j]);
                        m_allocator.destroy(old + j);
                    }
                    for (size_type j = i; j < m_size; ++j)
                    {
                        m_allocator.construct(m_data + j + 1, old[j]);
                        m_allocator.destroy(old + j);
                    }
                    if (old)
                    {
                        m_allocator.destroy(old, m_capacity);
                    }
                    m_capacity = m_size + 1;
                }
                m_allocator.construct(m_data + i, value);
                ++m_size;
            }
        }

        /**
         * Removes element from specified index.
         *
         * \throw std::out_of_range If index is out of bounds.
         */
        void erase(size_type pos)
        {
            if (pos >= m_size)
            {
                throw std::out_of_range("vector index out of bounds");
            }
            m_allocator.destroy(m_data + pos);
            std::memmove(
                    static_cast<void*>(m_data + pos),
                    static_cast<const void*>(m_data + pos + 1),
                    sizeof(value_type) * (--m_size - pos)
            );
        }

        /**
         * Inserts given element to the end of the vector.
         */
        void push_back(const_reference value)
        {
            reserve(m_size + 1);
            m_allocator.construct(m_data + m_size++, value);
        }

        /**
         * Inserts given element to the beginning of the vector.
         */
        void push_front(const_reference value)
        {
            if (m_capacity >= m_size + 1)
            {
                std::memmove(
                        static_cast<void*>(m_data + 1),
                        static_cast<const void*>(m_data),
                        sizeof(value_type) * m_size
                );
            } else {
                pointer old = m_data;

                m_data = m_allocator.allocate(m_capacity + 1);
                for (size_type i = 0; i < m_size; ++i)
                {
                    m_allocator.construct(m_data + i + 1, old[i]);
                    m_allocator.destroy(old + i);
                }
                if (old)
                {
                    m_allocator.deallocate(old, m_capacity);
                }
                ++m_capacity;
            }
            m_allocator.construct(m_data, value);
            ++m_size;
        }

        /**
         * Inserts given element to the end of the vector.
         */
        inline vector& operator<<(const_reference value)
        {
            push_back(value);

            return *this;
        }

        /**
         * Returns and removes last element from the vector.
         *
         * \throw std::out_of_range If vector is empty.
         */
        value_type pop_back()
        {
            if (m_size)
            {
                value_type element(m_data[--m_size]);

                m_allocator.destroy(m_data + m_size);

                return element;
            }

            throw std::out_of_range("vector is empty");
        }

        /**
         * Returns and removes first element from the vector.
         *
         * \throw std::out_of_range If vector is empty.
         */
        value_type pop_front()
        {
            if (m_size)
            {
                value_type element(m_data[0]);

                m_allocator.destroy(m_data);
                std::memmove(
                        static_cast<void*>(m_data),
                        static_cast<const void*>(m_data + 1),
                        sizeof(value_type) * --m_size
                );

                return element;
            }

            throw std::out_of_range("vector is empty");
        }

        /**
         * Removes last element from the vector and assigns it to the given
         * slot.
         *
         * \throw std::out_of_range If vector is empty.
         */
        inline vector& operator>>(reference value)
        {
            value = pop_back();

            return *this;
        }

        /**
         * Tests whether two vectors have equal contents.
         */
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
                    m_allocator.destroy(m_data + i);
                }
                if (m_capacity < that.m_size)
                {
                    if (m_data)
                    {
                        m_allocator.deallocate(m_data, m_capacity);
                    }
                    m_data = m_allocator.allocate(m_capacity = that.m_size);
                }
                for (size_type i = 0; i < that.m_size; ++i)
                {
                    m_allocator.construct(m_data + i, that.m_data[i]);
                }
                m_size = that.m_size;
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
        /** Allocator instance used for allocating memory. */
        allocator_type m_allocator;
        /** Size of the array. */
        size_type m_capacity;
        /** Number of elements stored in the array. */
        size_type m_size;
        /** Pointer to the array data. */
        pointer m_data;
    };

    /**
     * Outputs each element from the vector into the output stream, separated
     * by commas.
     */
    template <class T>
    std::ostream& operator<<(std::ostream& os, const vector<T>& v)
    {
        for (typename vector<T>::size_type i = 0; i < v.size(); ++i)
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
