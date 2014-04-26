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
#ifndef PEELO_TEXT_STRING_HPP_GUARD
#define PEELO_TEXT_STRING_HPP_GUARD

#include <peelo/text/rune.hpp>

namespace peelo
{
    class string
    {
    public:
        typedef std::size_t size_type;
        typedef rune value_type;
        typedef rune& reference;
        typedef const rune& const_reference;
        typedef rune* pointer;
        typedef const rune* const_pointer;

        static const size_type npos;

        /**
         * Constructs empty string.
         */
        string();

        /**
         * Copy constructor.
         */
        string(const string& that);

        string(const_pointer runes, size_type n);

        /**
         * Destructor.
         */
        virtual ~string();

        /**
         * Returns <code>true</code> if the string is empty.
         */
        inline bool empty() const
        {
            return !m_length;
        }

        /**
         * Returns length of the string.
         */
        inline size_type length() const
        {
            return m_length;
        }

        const_reference front() const;

        const_reference back() const;

        const_reference at(size_type pos) const;

        inline const_reference operator[](size_type pos) const
        {
            return m_runes[m_offset + pos];
        }

        string& assign(const string& that);

        inline string& operator=(const string& that)
        {
            return assign(that);
        }

        bool equals(const string& that) const;
        bool equals_icase(const string& that) const;

        inline bool operator==(const string& that) const
        {
            return equals(that);
        }

        inline bool operator!=(const string& that) const
        {
            return !equals(that);
        }

        string to_lower() const;

        string to_upper() const;

        /**
         * Returns <code>true</code> if every character in the string is in the
         * ASCII range.
         *
         * Returns <code>true</code> if the string is empty.
         */
        bool is_ascii() const;

    private:
        size_type m_offset;
        size_type m_length;
        pointer m_runes;
        unsigned* m_counter;
    };

    std::ostream& operator<<(std::ostream&, const string&);
}

#endif /* !PEELO_TEXT_STRING_HPP_GUARD */