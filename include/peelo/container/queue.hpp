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
#ifndef PEELO_CONTAINER_QUEUE_HPP_GUARD
#define PEELO_CONTAINER_QUEUE_HPP_GUARD

#include <peelo/container/vector.hpp>

namespace peelo
{
    template<
        class T,
        class Container = vector<T>
    >
    class queue
    {
    public:
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        explicit queue(const container_type& container = container_type())
            : m_container(container) {}

        queue(const queue<T, Container>& that)
            : m_container(that.m_container) {}

        queue& assign(const queue<T, Container>& that)
        {
            m_container = that.m_container;

            return *this;
        }

        /**
         * Assignment operator.
         */
        inline queue& operator=(const queue<T, Container>& that)
        {
            return assign(that);
        }

        /**
         * Returns reference to the first element in the queue.
         */
        inline reference front()
        {
            return m_container.front();
        }

        inline const_reference front() const
        {
            return m_container.front();
        }

        /**
         * Returns reference to the last element in the queue.
         */
        inline reference back()
        {
            return m_container.back();
        }

        inline const_reference back() const
        {
            return m_container.back();
        }

        /**
         * Returns <code>true</code> if the queue is not empty.
         */
        inline operator bool() const
        {
            return !m_container.empty();
        }

        /**
         * Returns <code>true</code> if the queue is empty.
         */
        inline bool operator!() const
        {
            return m_container.empty();
        }

        /**
         * Returns <code>true</code> if the queue is empty.
         */
        inline bool empty() const
        {
            return m_container.empty();
        }

        /**
         * Returns the number of elements in the underlying container.
         */
        inline size_type size() const
        {
            return m_container.size();
        }

        /**
         * Pushes the given element value to the end of the queue.
         */
        void push(const_reference value)
        {
            m_container.push_back(value);
        }

        /**
         * Pushes the given element value to the end of the queue.
         */
        inline queue& operator<<(const_reference value)
        {
            m_container.push_back(value);

            return *this;
        }

        /**
         * Removes an element from the front of the queue.
         */
        void pop()
        {
            m_container.pop_front();
        }

        /**
         * Removes an element from the front of the queue and assigns it to
         * the given slot.
         */
        queue& operator>>(reference slot)
        {
            slot = m_container.pop_front();

            return *this;
        }

        /**
         * Exchanges contents of the queue with contents of another queue.
         */
        void swap(queue<T, Container>& that)
        {
            m_container.swap(that.m_container);
        }

        /**
         * Removes all elements from the queue.
         */
        void clear()
        {
            m_container.clear();
        }

    private:
        /** The underlying container. */
        container_type m_container;
    };
}

#endif /* !PEELO_CONTAINER_QUEUE_HPP_GUARD */
