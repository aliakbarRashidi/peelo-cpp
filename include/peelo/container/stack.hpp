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
#ifndef PEELO_CONTAINER_STACK_HPP_GUARD
#define PEELO_CONTAINER_STACK_HPP_GUARD

#include <peelo/container/vector.hpp>

namespace peelo
{
    template<
        class T,
        class Container = vector<T>
    >
    class stack
    {
    public:
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

        explicit stack(const container_type& container = container_type())
            : m_container(container) {}

        stack(const stack<T, Container>& that)
            : m_container(that.m_container) {}

        /**
         * Replaces contents of the stack with contents of another stack.
         */
        stack& assign(const stack<T, Container>& that)
        {
            m_container = that.m_container;

            return *this;
        }

        /**
         * Assignment operator.
         */
        inline stack& operator=(const stack<T, Container>& that)
        {
            return assign(that);
        }

        /**
         * Returns reference to the top element in the stack.
         */
        inline reference top()
        {
            return m_container.back();
        }

        inline const_reference top() const
        {
            return m_container.back();
        }

        /**
         * Returns <code>true</code> if the stack is not empty.
         */
        inline operator bool() const
        {
            return !m_container.empty();
        }

        /**
         * Returns <code>true</code> if the stack is empty.
         */
        inline bool operator!() const
        {
            return m_container.empty();
        }

        /**
         * Returns <code>true</code> if the stack is empty.
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
         * Pushes the given element value to the top of the stack.
         */
        void push(const_reference value)
        {
            m_container.push_back(value);
        }
        
        /**
         * Pushes the given element value to the top of the stack.
         */
        inline stack& operator<<(const_reference value)
        {
            m_container.push_back(value);

            return *this;
        }

        /**
         * Removes the top element from the stack.
         */
        void pop()
        {
            m_container.pop_back();
        }

        /**
         * Exchanges contents of the queue with contents of another stack.
         */
        void swap(stack<T, Container>& that)
        {
            m_container.swap(that.m_container);
        }

    private:
        /** The underlying container. */
        container_type m_container;
    };
}

#endif /* !PEELO_CONTAINER_STACK_HPP_GUARD */
