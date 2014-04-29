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
    template <class T, class Container = vector<T> >
    class queue
    {
    public:
        typedef Container container_type;
        typedef Container::value_type value_type;
        typedef Container::size_type size_type;
        typedef Container::reference reference;
        typedef Container::const_reference const_reference;

        /**
         * Constructs empty queue.
         */
        queue()
            : m_container(Container()) {}

        /**
         * Copy constructor.
         */
        queue(const queue<T>& that)
            : m_container(that.m_container) {}

        /**
         * Constructs queue from existing container.
         */
        explicit queue(const Container& container)
            : m_container(container) {}

        queue& assign(const queue<T>& that)
        {
            m_container = that.m_container;

            return *this;
        }

        /**
         * Assignment operator.
         */
        inline queue& operator=(const queue<T>& that)
        {
            return assign(that);
        }

        inline operator bool() const
        {
            return !m_container.empty();
        }

        inline bool operator!() const
        {
            return m_container.empty();
        }

        inline reference front()
        {
            return m_container.front();
        }

        inline const_reference front()
        {
            return m_container.front();
        }

        inline reference back()
        {
            return m_container.back();
        }

        inline const_reference back()
        {
            return m_container.back();
        }

        inline bool empty() const
        {
            return m_container.empty();
        }

        inline size_type size() const
        {
            return m_container.size();
        }

        void push(const T& value)
        {
            m_container.push_back(value);
        }

        void pop()
        {
            m_container.pop_front();
        }

        void swap(queue<T>& that)
        {
            m_container.swap(that.m_container);
        }

        bool equals(const queue<T>& that) const
        {
            return m_container == that.m_container;
        }

        inline bool operator==(const queue<T>& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const queue<T>& that) const
        {
            return !equals(that);
        }

    private:
        /** Contains all elements stored in the queue. */
        container_type m_container;
    };
}

#endif /* !PEELO_CONTAINER_QUEUE_HPP_GUARD */
