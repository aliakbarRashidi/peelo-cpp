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
#ifndef PEELO_MEMORY_ARRAY_PTR_HPP_GUARD
#define PEELO_MEMORY_ARRAY_PTR_HPP_GUARD

namespace peelo
{
    /**
     * Shared pointer for arrays.
     */
    template< class T >
    class array_ptr
    {
    public:
        typedef T element_type;

        /**
         * Constructs <code>null</code> array.
         */
        array_ptr()
            : m_pointer(0)
            , m_counter(0) {}

        /**
         * Copy constructor.
         */
        array_ptr(const array_ptr<T>& that)
            : m_pointer(that.m_pointer)
            , m_counter(that.m_counter)
        {
            if (m_counter)
            {
                ++(*m_counter);
            }
        }

        /**
         * Constructs shared array pointer from given pointer.
         */
        template< class Y >
        explicit array_ptr(Y* pointer)
            : m_pointer(pointer)
            , m_counter(m_pointer ? new long(1) : 0) {}

        /**
         * Destructor.
         */
        virtual ~array_ptr()
        {
            if (m_counter && !--(*m_counter))
            {
                delete[] m_pointer;
                delete m_counter;
            }
        }

        inline operator bool() const
        {
            return m_pointer;
        }

        inline bool operator!() const
        {
            return !m_pointer;
        }

        void reset()
        {
            if (m_counter && !--(*m_counter))
            {
                delete[] m_pointer;
                delete m_counter;
                m_pointer = 0;
                m_counter = 0;
            }
        }

        void swap(array_ptr<T>& that)
        {
            if (m_pointer != that.m_pointer)
            {
                T* tmp_pointer = m_pointer;
                long* tmp_counter = m_counter;

                m_pointer = that.m_pointer;
                m_counter = that.m_counter;
                that.m_pointer = tmp_pointer;
                that.m_counter = tmp_counter;
            }
        }

        /**
         * Returns a pointer to the managed array.
         */
        inline T* get() const
        {
            return m_pointer;
        }

        inline T& operator*() const
        {
            return *m_pointer;
        }

        inline T& operator[](size_type pos) const
        {
            return m_pointer[pos];
        }

        inline long use_count() const
        {
            return m_counter ? *m_counter : 1;
        }

        inline bool unique() const
        {
            return use_count() == 1;
        }

        array_ptr& assign(const array_ptr<T>& that)
        {
            if (m_pointer != that.m_pointer)
            {
                if (m_counter && !--(*m_counter))
                {
                    delete[] m_pointer;
                    delete m_counter;
                }
                m_pointer = that.m_pointer;
                if ((m_counter = that.m_counter))
                {
                    ++(*m_counter);
                }
            }

            return *this;
        }

        inline array_ptr& operator=(const array_ptr<T>& that)
        {
            return assign(that);
        }

    private:
        /** The actual pointer. */
        T* m_pointer;
        /** Pointer to the counter data. */
        long* m_counter;
    };
}

#endif /* !PEELO_MEMORY_ARRAY_PTR_HPP_GUARD */
