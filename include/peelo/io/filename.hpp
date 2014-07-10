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
#ifndef PEELO_IO_FILENAME_HPP_GUARD
#define PEELO_IO_FILENAME_HPP_GUARD

#include <peelo/text/string.hpp>

namespace peelo
{
    class filename
    {
    public:
        /** Platform specific file name separator. */
        static const rune separator;

        /**
         * Constructs empty invalid file name.
         */
        filename();

        /**
         * Constructs copy of existing file name.
         */
        filename(const filename& that);

        /**
         * Parses an string into a file name.
         */
        filename(const string& str);

        static bool is_separator(const rune& r);

        /**
         * Returns <code>true</code> if the file name is empty.
         */
        bool empty() const;

        /**
         * Copies contents from another file name.
         */
        filename& assign(const filename& that);

        /**
         * Parses file name from given string.
         */
        filename& assign(const string& str);

        /**
         * Copy constructor.
         */
        inline filename& operator=(const filename& that)
        {
            return assign(that);
        }

        /**
         * Copy constructor.
         */
        inline filename& operator=(const string& str)
        {
            return assign(str);
        }

        /**
         * Tests whether two file names point to the same file.
         */
        bool equals(const filename& that) const;

        /**
         * Equality testing operator.
         */
        inline bool operator==(const filename& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const filename& that) const
        {
            return !equals(that);
        }

        /**
         * Compares two file names lexicographically against each other.
         */
        int compare(const filename& that) const;

        inline bool operator<(const filename& that) const
        {
            return compare(that) < 0;
        }

        inline bool operator>(const filename& that) const
        {
            return compare(that) > 0;
        }

        inline bool operator<=(const filename& that) const
        {
            return compare(that) <= 0;
        }

        inline bool operator>=(const filename& that) const
        {
            return compare(that) >= 0;
        }

        inline const string& file() const
        {
            return m_filename;
        }

        /**
         * Returns <code>true</code> if file name is absolute.
         */
        bool is_absolute() const;

        /**
         * Returns <code>true</code> if file name is pointing to a regular file
         * in the file system.
         */
        bool is_file() const;

        /**
         * Returns <code>true</code> if file name is pointing to a directory in
         * the file system.
         */
        bool is_dir() const;

        /**
         * Returns <code>true</code> if file name is pointing to a pipe in the
         * file system.
         */
        bool is_pipe() const;

        /**
         * Returns <code>true</code> if file name is pointing to a socket in
         * the file system.
         */
        bool is_socket() const;

        /**
         * Returns <code>true</code> if file name is pointing to a file which
         * has sticky bit set.
         */
        bool is_sticky() const;

        /**
         * Returns <code>true</code> if file name is pointing to a symbolic
         * link in the file system.
         */
        bool is_symlink() const;

        /**
         * Returns <code>true</code> if the file exists in the file system.
         */
        bool exists() const;

    private:
        string m_filename;
        string m_root;
        vector<string> m_path;
    };

    std::ostream& operator<<(std::ostream&, const filename&);

    template<>
    struct hash<filename>
    {
        typedef std::size_t result_type;

        result_type operator()(const filename& key) const
        {
            return hash<string>()(key.file());
        }
    };
}

#endif /* !PEELO_IO_FILENAME_HPP_GUARD */
