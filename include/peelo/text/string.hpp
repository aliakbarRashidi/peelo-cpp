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

#include <peelo/container/vector.hpp>
#include <peelo/text/rune.hpp>

namespace peelo
{
    class string
    {
    public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef rune value_type;
        typedef rune& reference;
        typedef const rune& const_reference;
        typedef rune* pointer;
        typedef const rune* const_pointer;
        struct iterator;
        typedef iterator const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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

        string(const iterator& begin, const iterator& end);

        /**
         * Constructs string from string literal. The input is expected to be
         * in UTF-8.
         */
        string(const char* input);

        /**
         * Destructor.
         */
        virtual ~string();

        /**
         * Constructs formatted string, using C printf as it's backend.
         */
        static string format(const char* format, ...);

        /**
         * Returns <code>true</code> if the string is not empty.
         */
        inline operator bool() const
        {
            return m_length;
        }

        /**
         * Returns <code>true</code> if the string is empty.
         */
        inline bool operator!() const
        {
            return !m_length;
        }

        /**
         * Returns <code>true</code> if the string is empty.
         */
        inline bool empty() const
        {
            return !m_length;
        }

        /**
         * Returns <code>true</code> if string is either empty or contains only
         * whitespace characters.
         */
        inline bool blank() const
        {
            return !m_length || is_space();
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

        iterator begin() const;

        iterator end() const;

        reverse_iterator rbegin() const;

        reverse_iterator rend() const;

        string& assign(const string& that);
        string& assign(const_reference rune);
        string& assign(const char* input);

        /**
         * Assignment operator.
         */
        inline string& operator=(const string& that)
        {
            return assign(that);
        }

        /**
         * Assignment operator.
         */
        inline string& operator=(const_reference rune)
        {
            return assign(rune);
        }

        /**
         * Assignment operator.
         */
        inline string& operator=(const char* input)
        {
            return assign(input);
        }

        bool equals(const string& that) const;
        bool equals_icase(const string& that) const;

        /**
         * Equality testing operator.
         */
        inline bool operator==(const string& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const string& that) const
        {
            return !equals(that);
        }

        int compare(const string& that) const;
        int compare_icase(const string& that) const;

        inline bool operator<(const string& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const string& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const string& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const string& that) const
        {
            return compare(that) >= 0;
        }

        string concat(const string& that) const;
        string concat(const_reference c) const;

        /**
         * Concatenation operator.
         */
        inline string operator+(const string& that) const
        {
            return concat(that);
        }

        /**
         * Concatenation operator.
         */
        inline string operator+(const_reference c) const
        {
            return concat(c);
        }

        /**
         * Clears contents of the string.
         */
        void clear();

        /**
         * Trims all whitespace from beginning and end of the string.
         */
        string trim() const;

        /**
         * Converts string into lower case and returns result.
         */
        string to_lower() const;

        /**
         * Converts string into upper case and returns result.
         */
        string to_upper() const;

        /**
         * Returns <code>true</code> if every character in the string is either
         * alphabetic or ASCII decimal digit character.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_alnum() const;

        /**
         * Returns <code>true</code> if every character in the string is
         * alphabetic character.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_alpha() const;

        /**
         * Returns <code>true</code> if every character in the string is in the
         * ASCII range.
         *
         * Returns <code>true</code> if the string is empty.
         */
        bool is_ascii() const;

        bool is_blank() const;

        /**
         * Returns <code>true</code> if every character in the string is a
         * control sequence.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_cntrl() const;

        /**
         * Returns <code>true</code> if every character in the string is ASCII
         * decimal digit character.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_digit() const;

        /**
         * Returns <code>true</code> if every character in the string is any
         * printing character, except space and other locale specific space
         * like characters.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_graph() const;

        /**
         * Returns <code>true</code> if every character in the string is a
         * lower case letter.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_lower() const;

        /**
         * Returns <code>true</code> if every character in the string is any
         * number character in any locale.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_number() const;

        /**
         * Returns <code>true</code> if every character in the string is any
         * printable character, including space.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_print() const;

        /**
         * Returns <code>true</code> if every character in the string is any
         * punctuation character, except space or alphanumeric character.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_punct() const;

        /**
         * Returns <code>true</code> if every character in the string is a
         * whitespace character.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_space() const;

        /**
         * Returns <code>true</code> if every character in the string is upper
         * case letter.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_upper() const;

        bool is_word() const;

        /**
         * Returns <code>true</code> if every character in the string is
         * hexadecimal character.
         *
         * Returns <code>false</code> if the string is empty.
         */
        bool is_xdigit() const;

        vector<char> utf8() const;
        vector<char> utf16be() const;
        vector<char> utf16le() const;
        vector<char> utf32be() const;
        vector<char> utf32le() const;
        vector<wchar_t> widen() const;

        size_type find(const string& str, size_type pos = 0) const;
        size_type find(const_pointer s, size_type pos, size_type count) const;
        size_type find(const_reference needle, size_type pos = 0) const;

        size_type rfind(const string& str, size_type pos = npos) const;
        size_type rfind(const_pointer s, size_type pos, size_type count) const;
        size_type rfind(const_reference needle, size_type pos = npos) const;

        string substr(size_type pos = 0, size_type count = npos) const;

        /**
         * Extracts all lines from the string and returns them in a vector of
         * substrings. All possible new line combinations are supported by this
         * method.
         */
        vector<string> lines() const;

        /**
         * Extracts all whitespace separated words from the string and returns
         * them in a vector of substrings.
         */
        vector<string> words() const;

        static string to_string(int n, int base = 10);
        static string to_string(unsigned int n, int base = 10);
        static string to_string(long n, int base = 10);
        static string to_string(unsigned long n, int base = 10);

    private:
        size_type m_offset;
        size_type m_length;
        pointer m_runes;
        unsigned* m_counter;
    };

    struct string::iterator : public std::iterator<
                              std::random_access_iterator_tag,
                              value_type,
                              difference_type,
                              const_pointer,
                              const_reference
    >
    {
    public:
        iterator();

        iterator(const iterator& that);

        iterator& operator=(const iterator& that);

        inline const_reference operator*() const
        {
            return *m_pointer;
        }

        inline const_pointer operator->() const
        {
            return m_pointer;
        }

        iterator& operator++();

        iterator operator++(int);

        iterator& operator--();

        iterator operator--(int);

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

        iterator operator+(size_type n) const;

        iterator operator-(size_type n) const;

        iterator& operator+=(size_type n);

        iterator& operator-=(size_type n);

        difference_type operator-(const iterator& that) const;

    private:
        pointer m_pointer;
        friend class string;
    };

    std::ostream& operator<<(std::ostream&, const string&);
    std::wostream& operator<<(std::wostream&, const string&);
    std::istream& getline(std::istream&, string&);
    std::wistream& getline(std::wistream&, string&);

    inline string operator+(const char* a, const string& b)
    {
        return string(a).concat(b);
    }

    template<>
    struct hash<string>
    {
        typedef std::size_t result_type;

        result_type operator()(const string& key) const
        {
            result_type result = 5381;

            for (string::size_type i = 0; i < key.length(); ++i)
            {
                result = ((result << 5) + result) + key[i].code();
            }

            return result;
        }
    };
}

#endif /* !PEELO_TEXT_STRING_HPP_GUARD */
