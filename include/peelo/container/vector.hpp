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
#include <iterator>
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
        typedef std::ptrdiff_t difference_type;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;

        struct iterator : public std::iterator<
                          std::random_access_iterator_tag,
                          value_type,
                          difference_type,
                          pointer,
                          reference
        >
        {
        public:
            iterator()
                : m_pointer(0) {}

            iterator(const iterator& that)
                : m_pointer(that.m_pointer) {}

            iterator& operator=(const iterator& that)
            {
                m_pointer = that.m_pointer;

                return *this;
            }

            inline reference operator*()
            {
                return *m_pointer;
            }

            inline pointer operator->()
            {
                return m_pointer;
            }

            iterator& operator++()
            {
                ++m_pointer;

                return *this;
            }

            iterator operator++(int)
            {
                iterator tmp(*this);

                ++m_pointer;

                return *this;
            }

            iterator& operator--()
            {
                --m_pointer;

                return *this;
            }

            iterator operator--(int)
            {
                iterator tmp(*this);

                --m_pointer;

                return *this;
            }

            inline bool operator==(const iterator& that) const
            {
                return m_pointer == that.m_pointer;
            }

            inline bool operator!=(const iterator& that) const
            {
                return m_pointer != that.m_pointer;
            }

            inline bool operator<(const iterator& that) const
            {
                return m_pointer < that.m_pointer;
            }

            inline bool operator>(const iterator& that) const
            {
                return m_pointer > that.m_pointer;
            }

            inline bool operator<=(const iterator& that) const
            {
                return m_pointer <= that.m_pointer;
            }

            inline bool operator>=(const iterator& that) const
            {
                return m_pointer >= that.m_pointer;
            }

            inline reference operator[](size_type n)
            {
                return m_pointer[n];
            }

            iterator operator+(size_type n) const
            {
                iterator result(*this);

                result.m_pointer += n;

                return result;
            }

            iterator operator-(size_type n) const
            {
                iterator result(*this);

                result.m_pointer -= n;

                return result;
            }

            iterator& operator+=(size_type n)
            {
                m_pointer += n;

                return *this;
            }

            iterator& operator-=(size_type n)
            {
                m_pointer -= n;

                return *this;
            }

            difference_type operator-(const iterator& that) const
            {
                return m_pointer - that.m_pointer;
            }

        private:
            pointer m_pointer;
            friend class vector;
        };

        struct const_iterator : public std::iterator<
                                std::random_access_iterator_tag,
                                value_type,
                                difference_type,
                                const_pointer,
                                const_reference
        >
        {
        public:
            const_iterator()
                : m_pointer(0) {}

            const_iterator(const iterator& that)
                : m_pointer(that.m_pointer) {}

            const_iterator& operator=(const const_iterator& that)
            {
                m_pointer = that.m_pointer;

                return *this;
            }

            inline const_reference operator*()
            {
                return *m_pointer;
            }

            inline const_pointer operator->()
            {
                return m_pointer;
            }

            const_iterator& operator++()
            {
                ++m_pointer;

                return *this;
            }

            const_iterator operator++(int)
            {
                const_iterator tmp(*this);

                ++m_pointer;

                return *this;
            }

            const_iterator& operator--()
            {
                --m_pointer;

                return *this;
            }

            const_iterator operator--(int)
            {
                const_iterator tmp(*this);

                --m_pointer;

                return *this;
            }

            inline bool operator==(const const_iterator& that) const
            {
                return m_pointer == that.m_pointer;
            }

            inline bool operator!=(const const_iterator& that) const
            {
                return m_pointer != that.m_pointer;
            }

            inline bool operator<(const const_iterator& that) const
            {
                return m_pointer < that.m_pointer;
            }

            inline bool operator>(const const_iterator& that) const
            {
                return m_pointer > that.m_pointer;
            }

            inline bool operator<=(const const_iterator& that) const
            {
                return m_pointer <= that.m_pointer;
            }

            inline bool operator>=(const const_iterator& that) const
            {
                return m_pointer >= that.m_pointer;
            }

            inline const_reference operator[](size_type n)
            {
                return m_pointer[n];
            }

            const_iterator operator+(size_type n) const
            {
                const_iterator result(*this);

                result.m_pointer += n;

                return result;
            }

            const_iterator operator-(size_type n) const
            {
                const_iterator result(*this);

                result.m_pointer -= n;

                return result;
            }

            const_iterator& operator+=(size_type n)
            {
                m_pointer += n;

                return *this;
            }

            const_iterator& operator-=(size_type n)
            {
                m_pointer -= n;

                return *this;
            }

            difference_type operator-(const const_iterator& that) const
            {
                return m_pointer - that.m_pointer;
            }

        private:
            const_pointer m_pointer;
            friend class vector;
        };

        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        /**
         * Constructs empty vector.
         */
        vector()
            : m_allocator(allocator_type())
            , m_capacity(0)
            , m_size(0)
            , m_data(0) {}

        /**
         * Constructs empty vector.
         *
         * \param allocator Allocator used for allocating memory
         */
        explicit vector(const allocator_type& allocator)
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
        vector(size_type count,
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
         * Constructs vector which with <i>count</i> value-initializeed
         * instances of <i>value_type</i>. No copies are made.
         */
        explicit vector(size_type count,
                        const allocator_type& allocator = allocator_type())
            : m_allocator(allocator)
            , m_capacity(count)
            , m_size(count)
            , m_data(m_size ? m_allocator.allocate(m_size) : 0)
        {
            for (size_type i = 0; i < m_size; ++i)
            {
                m_allocator.construct(m_data + i, value_type());
            }
        }

        /**
         * Constructs vector with contents of the range <i>[first, last]</i>.
         */
        template< class InputIt >
        vector(InputIt first,
               InputIt last,
               const allocator_type& allocator = allocator_type())
            : m_allocator(allocator)
            , m_capacity(std::distance(first, last))
            , m_size(m_capacity)
            , m_data(m_size ? m_allocator.allocate(m_size) : 0)
        {
            size_type index = 0;

            for (; first != last; ++first)
            {
                m_allocator.construct(m_data + index++, *first);
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

        /**
         * Returns the number of elements stored in the vector.
         */
        inline size_type size() const
        {
            return m_size;
        }

        /**
         * Returns an iterator to the first element of the vector.
         */
        iterator begin()
        {
            iterator i;

            i.m_pointer = m_data;

            return i;
        }

        const_iterator begin() const
        {
            const_iterator i;

            i.m_pointer = m_data;

            return i;
        }

        inline const_iterator cbegin() const
        {
            return begin();
        }

        /**
         * Returns an iterator to the element following the last element of the
         * vector.
         */
        iterator end()
        {
            iterator i;

            i.m_pointer = m_data + m_size;

            return i;
        }

        const_iterator end() const
        {
            const_iterator i;

            i.m_pointer = m_data + m_size;

            return i;
        }

        inline const_iterator cend() const
        {
            return end();
        }

        inline reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        inline const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        inline const_reverse_iterator crbegin() const
        {
            return rbegin();
        }

        inline reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        inline const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        inline const_reverse_iterator crend() const
        {
            return rend();
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
            insert(i, 1, value);
        }

        void insert(size_type i, size_type count, const_reference value)
        {
            if (i >= m_size)
            {
                throw std::out_of_range("vector index out of range");
            }
            else if (!count)
            {
                return;
            }
            else if (!i)
            {
                push_front(count, value);
            }
            else if (i == m_size)
            {
                push_back(count, value);
            } else {
                if (m_capacity >= m_size + count)
                {
                    std::memmove(
                            static_cast<void*>(m_data + i + count),
                            static_cast<const void*>(m_data + i),
                            sizeof(value_type) * (m_size - i)
                    );
                } else {
                    pointer old = m_data;

                    m_data = m_allocator.allocate(m_size + count);
                    for (size_type j = 0; j < i - count; ++j)
                    {
                        m_allocator.construct(m_data + j, old[j]);
                        m_allocator.destroy(old + j);
                    }
                    for (size_type j = i; j < m_size; ++j)
                    {
                        m_allocator.construct(m_data + j + count, old[j]);
                        m_allocator.destroy(old + j);
                    }
                    if (old)
                    {
                        m_allocator.destroy(old, m_capacity);
                    }
                    m_capacity = m_size + count;
                }
                for (size_type j = 0; j < count; ++j)
                {
                    m_allocator.construct(m_data + i + j, value);
                }
                m_size += count;
            }
        }

        void insert(const const_iterator& pos, const_reference& value)
        {
            insert(pos.m_pointer - m_data, value);
        }

        void insert(const const_iterator& pos,
                    size_type count,
                    const_reference& value)
        {
            insert(pos.m_pointer - m_data, count, value);
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
    template< class T >
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

    /**
     * Outputs each element from the vector into the output stream, separated
     * by commas.
     */
    template< class T >
    std::wostream& operator<<(std::wostream& os, const vector<T>& v)
    {
        for (typename vector<T>::size_type i = 0; i < v.size(); ++i)
        {
            if (i > 0)
            {
                os << L", ";
            }
            os << v[i];
        }

        return os;
    }
}

#endif /* !PEELO_CONTAINER_VECTOR_HPP_GUARD */
