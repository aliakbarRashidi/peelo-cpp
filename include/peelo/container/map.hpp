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
#ifndef PEELO_CONTAINER_MAP_HPP_GUARD
#define PEELO_CONTAINER_MAP_HPP_GUARD

#include <peelo/container/pair.hpp>
#include <peelo/functional/equal_to.hpp>
#include <peelo/functional/hash.hpp>
#include <iterator>
#include <memory>

namespace peelo
{
    /**
     * Hash map implementation.
     */
    template <
        class Key,
        class T,
        class Hash = hash<Key>,
        class KeyEqual = equal_to<Key>,
        class Allocator = std::allocator< pair<const Key, T> >
    >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_value;
        typedef pair<const Key, T> value_type;
        typedef std::size_t size_type;
        typedef Hash hasher;
        typedef KeyEqual key_equal;
        typedef Allocator allocator_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;

        explicit map(size_type bucket_count = 8,
                     const hasher& hash = hasher(),
                     const key_equal& equal = key_equal(),
                     const allocator_type& allocator = allocator_type())
            : m_bucket_count(bucket_count)
            , m_hash(hash)
            , m_equal(equal)
            , m_allocator(allocator)
            , m_bucket(new entry*[m_bucket_count])
            , m_front(0)
            , m_back(0)
            , m_size(0)
        {
            for (size_type i = 0; i < m_bucket_count; ++i)
            {
                m_bucket[i] = 0;
            }
        }

        /**
         * Copy constructor.
         */
        explicit map(const map<Key, T, Hash, KeyEqual, Allocator>& that)
            : m_bucket_count(that.m_bucket_count)
            , m_hash(that.m_hash)
            , m_equal(that.m_equal)
            , m_allocator(that.m_allocator)
            , m_bucket(new entry*[m_bucket_count])
            , m_front(0)
            , m_back(0)
            , m_size(0)
        {
            for (size_type i = 0; i < m_bucket_count; ++i)
            {
                m_bucket[i] = 0;
            }
            for (const entry* e1 = that.m_front; e1; e1 = e1->next)
            {
                entry* e2 = static_cast<entry*>(std::malloc(sizeof(entry)));
                const size_type index = static_cast<size_type>(e1->hash % m_bucket_count);

                m_allocator.construct(&e2->data, e1->data);
                e2->hash = e1->hash;
                e2->next = 0;
                if ((e2->prev = m_back))
                {
                    m_back->next = e2;
                } else {
                    m_front = e2;
                }
                m_back = e2;
                e2->child = m_bucket[index];
                m_bucket[index] = e2;
                ++m_size;
            }
        }

        /**
         * Destructor.
         */
        virtual ~map()
        {
            entry* current = m_front;
            entry* next;

            while (current)
            {
                next = current->next;
                m_allocator.destroy(&current->data);
                std::free(static_cast<void*>(current));
                current = next;
            }
            delete[] m_bucket;
        }

        /**
         * Returns <code>true</code> if the map is not empty.
         */
        inline operator bool() const
        {
            return m_size;
        }

        /**
         * Returns <code>true</code> if the map is empty.
         */
        inline bool operator!() const
        {
            return !m_size;
        }

        /**
         * Returns <code>true</code> if the map is empty.
         */
        inline bool empty() const
        {
            return !m_size;
        }

        /**
         * Returns the number of elements stored in the map.
         */
        inline size_type size() const
        {
            return m_size;
        }

        reference at(const key_type& key)
        {
            const typename hasher::result_type hash = m_hash(key);
            const size_type index = static_cast<size_type>(hash % m_bucket_count);

            for (entry* e = m_bucket[index]; e; e = e->child)
            {
                if (e->hash == hash && m_equal(e->data.first(), key))
                {
                    return e->data;
                }
            }

            throw std::out_of_range("map index out of bounds");
        }

        const_reference at(const key_type& key) const
        {
            const typename hasher::result_type hash = m_hash(key);
            const size_type index = static_cast<size_type>(hash % m_bucket_count);

            for (entry* e = m_bucket[index]; e; e = e->child)
            {
                if (e->hash == hash && m_equal(e->data.first(), key))
                {
                    return e->data;
                }
            }

            throw std::out_of_range("map index out of bounds");
        }

        mapped_value& operator[](const key_type& key)
        {
            const typename hasher::result_type hash = m_hash(key);
            const size_type index = static_cast<size_type>(hash % m_bucket_count);
            entry* e;

            for (e = m_bucket[index]; e; e = e->child)
            {
                if (e->hash == hash && m_equal(e->data.first(), key))
                {
                    return e->data.second();
                }
            }
            e = static_cast<entry*>(std::malloc(sizeof(entry)));
            m_allocator.construct(&e->data, value_type(key, mapped_value()));
            e->hash = hash;
            e->next = 0;
            if ((e->prev = m_back))
            {
                m_back->next = e;
            } else {
                m_front = e;
            }
            m_back = e;
            e->child = m_bucket[index];
            m_bucket[index] = e;
            ++m_size;

            return e->data.second();
        }

        map& assign(const map<Key, T>& that)
        {
            clear();
            for (const entry* e1 = that.m_front; e1; e1 = e1->next)
            {
                entry* e2 = static_cast<entry*>(std::malloc(sizeof(entry)));
                const size_type index = static_cast<size_type>(e1->hash % m_bucket_count);

                m_allocator.construct(&e2->data, e1->data);
                e2->hash = e1->hash;
                e2->next = 0;
                if ((e2->prev = m_back))
                {
                    m_back->next = e2;
                } else {
                    m_front = e2;
                }
                m_back = e2;
                e2->child = m_bucket[index];
                m_bucket[index] = e2;
                ++m_size;
            }

            return *this;
        }

        /**
         * Assignment operator.
         */
        inline map& operator=(const map<Key, T>& that)
        {
            return assign(that);
        }

        /**
         * Removes all entries from the set.
         */
        void clear()
        {
            entry* current = m_front;
            entry* next;

            while (current)
            {
                next = current->next;
                m_allocator.destroy(&current->data);
                std::free(static_cast<void*>(current));
                current = next;
            }
            for (size_type i = 0; i < m_bucket_count; ++i)
            {
                m_bucket[i] = 0;
            }
            m_front = m_back = 0;
            m_size = 0;
        }

        /**
         * Inserts given element into the map, if the map doesn't already
         * contain an element with an equivalent key.
         */
        void insert(const_reference value)
        {
            const typename hasher::result_type hash = m_hash(value.first());
            const size_type index = static_cast<size_type>(hash % m_bucket_count);
            entry* e;

            for (e = m_bucket[index]; e; e = e->child)
            {
                if (e->hash == hash && m_equal(e->data.first(), value.first()))
                {
                    return;
                }
            }
            e = static_cast<entry*>(std::malloc(sizeof(entry)));
            m_allocator.construct(&e->data, value);
            e->hash = hash;
            e->next = 0;
            if ((e->prev = m_back))
            {
                m_back->next = e;
            } else {
                m_front = e;
            }
            m_back = e;
            e->child = m_bucket[index];
            m_bucket[index] = e;
            ++m_size;
        }

        /**
         * Inserts given key and value into the map. Existing entries with same
         * key are overridden.
         */
        void insert(const key_type& key, const mapped_value& value)
        {
            const typename hasher::result_type hash = m_hash(key);
            const size_type index = static_cast<size_type>(hash % m_bucket_count);
            entry* e;

            for (e = m_bucket[index]; e; e = e->child)
            {
                if (e->hash == hash && m_equal(e->data.first(), key))
                {
                    e->data.second() = value;
                    return;
                }
            }
            e = static_cast<entry*>(std::malloc(sizeof(entry)));
            m_allocator.construct(&e->data, value_type(key, value));
            e->hash = hash;
            e->next = 0;
            if ((e->prev = m_back))
            {
                m_back->next = e;
            } else {
                m_front = e;
            }
            m_back = e;
            e->child = m_bucket[index];
            m_bucket[index] = e;
            ++m_size;
        }

        inline map& operator<<(const_reference value)
        {
            insert(value);

            return *this;
        }

        size_type erase(const_reference value)
        {
            const typename hasher::result_type hash = m_hash(value.first());
            const size_type index = static_cast<size_type>(hash % m_bucket_count);
            entry* e = m_bucket[index];

            if (e)
            {
                size_type result = 0;
                entry* ancestor = 0;
                entry* child;

                do
                {
                    child = e->child;
                    if (e->hash == hash && m_equal(e->data.first(), value.first()))
                    {
                        if (e->next && e->prev)
                        {
                            e->next->prev = e->prev;
                            e->prev->next = e->next;
                        }
                        else if (e->next)
                        {
                            e->next->prev = 0;
                            m_front = e->next;
                        }
                        else if (e->prev)
                        {
                            e->prev->next = 0;
                            m_back = e->prev;
                        } else {
                            m_front = m_back = 0;
                        }
                        m_allocator.destroy(&e->data);
                        std::free(static_cast<void*>(e));
                        ++result;
                        --m_size;
                        if (ancestor)
                        {
                            ancestor->child = child;
                        } else {
                            m_bucket[index] = child;
                        }
                    } else {
                        ancestor = e;
                    }
                    e = child;
                }
                while (e);

                return result;
            }

            return 0;
        }

    private:
        struct entry
        {
            typename hasher::result_type hash;
            value_type data;
            entry* next;
            entry* prev;
            entry* child;
        };

    public:
        class iterator : public std::iterator<
                         std::bidirectional_iterator_tag,
                         value_type
        >
        {
        public:
            iterator()
                : m_current(0) {}

            iterator(const iterator& that)
                : m_current(that.m_current) {}

            iterator& operator=(const iterator& that)
            {
                m_current = that.m_current;

                return *this;
            }

            iterator& operator++()
            {
                if (m_current)
                {
                    m_current = m_current->next;
                }

                return *this;
            }

            iterator operator++(int)
            {
                iterator tmp(*this);

                operator++();

                return tmp;
            }

            iterator& operator--()
            {
                if (m_current)
                {
                    m_current = m_current->prev;
                }

                return *this;
            }

            iterator& operator--(int)
            {
                iterator tmp(*this);

                operator--();

                return tmp;
            }

            inline bool operator==(const iterator& that) const
            {
                return m_current == that.m_current;
            }

            inline bool operator!=(const iterator& that) const
            {
                return m_current != that.m_current;
            }

            inline reference operator*()
            {
                return m_current->data;
            }

            inline const_reference operator*() const
            {
                return m_current->data;
            }

            inline reference operator->()
            {
                return m_current->data;
            }

            inline const_reference operator->() const
            {
                return m_current->data;
            }

        private:
            entry* m_current;
            friend class map;
        };

        typedef iterator const_iterator;

        inline iterator begin()
        {
            iterator i;

            i.m_current = m_front;

            return i;
        }

        inline const_iterator begin() const
        {
            const_iterator i;

            i.m_current = m_front;

            return i;
        }

        inline const_iterator cbegin() const
        {
            const_iterator i;

            i.m_current = m_front;

            return i;
        }

        inline iterator end()
        {
            return iterator();
        }

        inline const_iterator end() const
        {
            return const_iterator();
        }

        inline const_iterator cend() const
        {
            return const_iterator();
        }

        iterator find(const key_type& key)
        {
            const typename hasher::result_type hash = m_hash(key);
            const size_type index = static_cast<size_type>(hash % m_bucket_count);

            for (entry* e = m_bucket[index]; e; e = e->child)
            {
                if (e->hash == hash && m_equal(e->data.first(), key))
                {
                    iterator i;

                    i.m_current = e;

                    return i;
                }
            }

            return iterator();
        }

        const_iterator find(const key_type& key) const
        {
            const typename hasher::result_type hash = m_hash(key);
            const size_type index = static_cast<size_type>(hash % m_bucket_count);

            for (entry* e = m_bucket[index]; e; e = e->child)
            {
                if (e->hash == hash && m_equal(e->data.first(), key))
                {
                    const_iterator i;

                    i.m_current = e;

                    return i;
                }
            }

            return const_iterator();
        }

    private:
        const size_type m_bucket_count;
        hasher m_hash;
        key_equal m_equal;
        allocator_type m_allocator;
        entry** m_bucket;
        entry* m_front;
        entry* m_back;
        size_type m_size;
    };
}

#endif /* !PEELO_CONTAINER_MAP_HPP_GUARD */
