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
#ifndef PEELO_TEXT_STRINGBUILDER_HPP_GUARD
#define PEELO_TEXT_STRINGBUILDER_HPP_GUARD

#include <peelo/text/string.hpp>

namespace peelo
{
    /**
     * Class which can be used for constructing strings.
     */
    class stringbuilder
    {
    public:
        typedef rune value_type;
        typedef std::size_t size_type;
        typedef rune& reference;
        typedef const rune& const_reference;
        typedef rune* pointer;
        typedef const rune* const_pointer;

        /**
         * Constructs empty string builder.
         *
         * \param allocator Allocator used for allocating memory
         */
        stringbuilder();

        /**
         * Constructs copy of existing string builder.
         */
        stringbuilder(const stringbuilder& that);

        /**
         * Constructs string builder from contents of the given string.
         */
        stringbuilder(const string& str);

        /**
         * Destructor.
         */
        virtual ~stringbuilder();

        /**
         * Constructs a string from contents of the string builder.
         */
        string str() const;

        /**
         * Returns <code>true</code> if the string builder is not empty.
         */
        inline operator bool() const
        {
            return m_length;
        }

        /**
         * Returns <code>true</code> if the string builder is empty.
         */
        inline bool operator!() const
        {
            return !m_length;
        }

        /**
         * Returns a reference to rune at specified location, with bounds
         * checking.
         *
         * If <i>pos</i> is not within the range of the string builder, an
         * exception of type std::out_of_range is thrown.
         *
         * \throw std::out_of_range If index is out of bounds.
         */
        reference at(size_type pos);

        const_reference at(size_type pos) const;

        /**
         * Returns reference to rune at specified location. No bounds checking
         * is performed.
         */
        inline reference operator[](size_type pos)
        {
            return m_runes[pos];
        }

        inline const_reference operator[](size_type pos) const
        {
            return m_runes[pos];
        }

        /**
         * Returns reference to the first rune stored in the string builder.
         *
         * Calling front on empty string builder is undefined.
         */
        inline reference front()
        {
            return m_runes[0];
        }

        inline const_reference front() const
        {
            return m_runes[0];
        }

        /**
         * Returns reference to the last rune in the string builder.
         *
         * Calling back on empty string builder is undefined.
         */
        inline reference back()
        {
            return m_runes[m_length - 1];
        }

        inline const_reference back() const
        {
            return m_runes[m_length - 1];
        }

        /**
         * Returns pointer to the underlying array serving as storage. The
         * returned pointer may be NULL if the string builder is empty.
         */
        inline pointer runes()
        {
            return m_runes;
        }

        inline const_pointer runes() const
        {
            return m_runes;
        }

        /**
         * Returns <code>true</code> if the string builder is empty.
         */
        inline bool empty() const
        {
            return !m_length;
        }

        /**
         * Returns length of the data currently stored in the string builder.
         */
        inline size_type length() const
        {
            return m_length;
        }

        /**
         * Ensures that the string builder has capacity for at least <i>n</i>
         * runes.
         */
        void reserve(size_type n);

        /**
         * Returns current capacity of the string builder.
         */
        inline size_type capacity() const
        {
            return m_capacity;
        }

        /**
         * Removes all runes from the string builder.
         */
        void clear();

        /**
         * Inserts given rune at index position <i>i</i> in the string builder.
         * If <i>i</i> is <code>0</code>, then rune is prepended to the string
         * builder. If <i>i</i> is length(), then rune is appended to the
         * string builder.
         *
         * \throw std::out_of_range If index is out of bounds
         */
        void insert(size_type i, const_reference value);

        void insert(size_type i, size_type count, const_reference value);

        void insert(size_type i, const string& str);

        /**
         * Removes rune from specified index.
         *
         * \throw std::out_of_range If index is out of bounds.
         */
        void erase(size_type pos);

        /**
         * Inserts given rune to the end of the string builder.
         */
        void append(const_reference value);

        void append(size_type count, const_reference value);

        /**
         * Inserts given string to the end of the string builder.
         */
        void append(const string& str);

        /**
         * Inserts given rune to the end of the string builder.
         */
        inline stringbuilder& operator<<(const_reference value)
        {
            append(value);

            return *this;
        }

        /**
         * Inserts given string to the end of the string builder.
         */
        inline stringbuilder& operator<<(const string& str)
        {
            append(str);

            return *this;
        }

        /**
         * Inserts given rune at the beginning of the string builder.
         */
        void prepend(const_reference value);

        void prepend(size_type count, const_reference value);

        /**
         * Inserts given string at the beginning of the string builder.
         */
        void prepend(const string& str);

        /**
         * Tests whether two string builder have equal contents.
         */
        bool equals(const stringbuilder& that) const;

        /**
         * Equality testing operator.
         */
        inline bool operator==(const stringbuilder& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const stringbuilder& that) const
        {
            return !equals(that);
        }

        stringbuilder& assign(const stringbuilder& that);
        stringbuilder& assign(const string& str);

        /**
         * Assignment operator.
         */
        inline stringbuilder& operator=(const stringbuilder& that)
        {
            return assign(that);
        }

        /**
         * Assignment operator.
         */
        inline stringbuilder& operator=(const string& str)
        {
            return assign(str);
        }

    private:
        /** Current capacity of the string builder. */
        size_type m_capacity;
        /** Number of runes stored in the string builder. */
        size_type m_length;
        /** Pointer to the rune data. */
        pointer m_runes;
    };
}

#endif /* !PEELO_TEXT_STRINGBUILDER_HPP_GUARD */
