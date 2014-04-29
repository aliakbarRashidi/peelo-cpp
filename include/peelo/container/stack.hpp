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
    /**
     * Stack class is a template class which provides a stack implementation.
     *
     * A stack is last in, first out (LIFO) structure. Items are added to the
     * top of the stack using push() and retrieved from the top using pop().
     * The top() function provides access to the topmost item without removing
     * it.
     */
    template <class T, class Container = vector<T> >
    class stack
    {
    public:
        typedef Container container_type;
        typedef Container::value_type value_type;
        typedef Container::size_type size_type;
        typedef Container::reference reference;
        typedef Container::const_reference const_reference;

        inline reference top()
        {
            return m_container.back();
        }

        inline const_reference top() const
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

        void push(const_reference value)
        {
            m_container.push_back(value);
        }

        inline stack& operator<<(const_reference value)
        {
            push(value);

            return *this;
        }

        inline void pop()
        {
            m_container.pop_back();
        }

        void swap(stack<T, Container>& that)
        {
            m_container.swap(that.m_container);
        }

        bool equals(const stack<T, Container>& that) const
        {
            return m_container == that.m_container;
        }

        inline bool operator==(const stack<T, Container>& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const stack<T, Container>& that) const
        {
            return !equals(that);
        }

    private:
        /** Contains all elements stored in the stack. */
        container_type m_container;
    };
}

#endif /* !PEELO_CONTAINER_STACK_HPP_GUARD */
