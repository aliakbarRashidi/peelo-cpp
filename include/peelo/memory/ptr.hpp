#ifndef PEELO_MEMORY_PTR_HPP_GUARD
#define PEELO_MEMORY_PTR_HPP_GUARD

namespace peelo
{
    /**
     * Minimal shared pointer implementation.
     */
    template< class T >
    class ptr
    {
    public:
        typedef T element_type;

        /**
         * Constructs <code>null</code> pointer.
         */
        ptr()
            : m_pointer(0)
            , m_counter(0) {}

        /**
         * Copy constructor.
         */
        ptr(const ptr<T>& that)
            : m_pointer(that.m_pointer)
            , m_counter(that.m_counter)
        {
            if (m_counter)
            {
                ++(*m_counter);
            }
        }

        /**
         * Constructs shared pointer from given pointer.
         */
        template< class Y >
        explicit ptr(Y* pointer)
            : m_pointer(pointer)
            , m_counter(m_pointer ? new long(1) : 0) {}

        /**
         * Destructor.
         */
        virtual ~ptr()
        {
            if (m_counter && !--(*m_counter))
            {
                delete m_pointer;
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
                delete m_pointer;
                delete m_counter;
                m_pointer = 0;
                m_counter = 0;
            }
        }

        void swap(ptr<T>& that)
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
         * Returns a pointer to the managed object.
         */
        inline T* get() const
        {
            return m_pointer;
        }

        inline T& operator*() const
        {
            return *m_pointer;
        }

        inline T* operator->() const
        {
            return m_pointer;
        }

        inline long use_count() const
        {
            return m_counter ? *m_counter : 1;
        }

        inline bool unique() const
        {
            return use_count() == 1;
        }

        ptr& assign(const ptr<T>& that)
        {
            if (m_pointer != that.m_pointer)
            {
                if (m_counter && !--(*m_counter))
                {
                    delete m_pointer;
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

        inline ptr& operator=(const ptr<T>& that)
        {
            return assign(that);
        }

    private:
        /** The actual pointer. */
        T* m_pointer;
        /** Pointer to counter data. */
        long* m_counter;
    };
}

#endif /* !PEELO_MEMORY_PTR_HPP_GUARD */
