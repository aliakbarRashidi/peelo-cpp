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
#ifndef PEELO_IO_FILEPATH_HPP_GUARD
#define PEELO_IO_FILEPATH_HPP_GUARD

#include <peelo/container/set.hpp>
#include <peelo/io/filename.hpp>

namespace peelo
{
    class filepath
    {
    public:
        static const rune separator;

        /**
         * Constructs empty file path.
         */
        filepath();

        /**
         * Constructs copy of existing file path.
         */
        filepath(const filepath& that);

        /**
         * Constructs file path from existing set of file names.
         */
        filepath(const set<filename>& filenames);

        /**
         * Parses file path from a string.
         */
        filepath(const string& str);

        static bool is_separator(const rune& r);

        filepath& assign(const filepath& that);
        filepath& assign(const set<filename>& filenames);
        filepath& assign(const string& str);

        /**
         * Assignment operator.
         */
        inline filepath& operator=(const filepath& that)
        {
            return assign(that);
        }

        /**
         * Assignment operator.
         */
        inline filepath& operator=(const set<filename>& filenames)
        {
            return assign(filenames);
        }

        /**
         * Assignment operator.
         */
        inline filepath& operator=(const string& str)
        {
            return assign(str);
        }

        bool equals(const filepath& that) const;

        /**
         * Equality testing operator.
         */
        inline bool operator==(const filepath& that) const
        {
            return equals(that);
        }

        /**
         * Non-equality testing operator.
         */
        inline bool operator!=(const filepath& that) const
        {
            return !equals(that);
        }

    private:
        set<filename> m_filenames;
    };
}

#endif /* !PEELO_IO_FILEPATH_HPP_GUARD */
