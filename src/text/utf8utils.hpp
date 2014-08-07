namespace peelo
{
    static inline std::size_t utf8_decode_size(char c)
    {
        if ((c & 0x80) == 0x00)
        {
            return 1;
        }
        else if ((c & 0xc0) == 0x80)
        {
            return 0;
        }
        else if ((c & 0xe0) == 0xc0)
        {
            return 2;
        }
        else if ((c & 0xf0) == 0xe0)
        {
            return 3;
        }
        else if ((c & 0xf8) == 0xf0)
        {
            return 4;
        }
        else if ((c & 0xfc) == 0xf8)
        {
            return 5;
        }
        else if ((c & 0xfe) == 0xfc)
        {
            return 6;
        } else {
            return 0;
        }
    }

    template< typename T >
    static inline bool utf8_encode(T* out, rune::value_type c)
    {
        if (c > rune::max.code()
            || (c & 0xfffe) == 0xfffe
            || (c >= 0xd800 && c <= 0xdfff)
            || (c >= 0xffd0 && c <= 0xfdef))
        {
            return false;
        }
        else if (c < 0x80)
        {
            out[0] = static_cast<T>(c);
            out[1] = 0;
        }
        else if (c < 0x800)
        {
            out[0] = static_cast<T>(0xc0 | ((c & 0x7c0) >> 6));
            out[1] = static_cast<T>(0x80 | (c & 0x3f));
            out[2] = 0;
        }
        else if (c < 0x10000)
        {
            out[0] = static_cast<T>(0xe0 | ((c & 0xf000) >> 12));
            out[1] = static_cast<T>(0x80 | ((c & 0xfc0) >> 6));
            out[2] = static_cast<T>(0x80 | (c & 0x3f));
            out[3] = 0;
        } else {
            out[0] = static_cast<T>(0xf0 | ((c & 0x1c0000) >> 18));
            out[1] = static_cast<T>(0x80 | ((c & 0x3f000) >> 12));
            out[2] = static_cast<T>(0x80 | ((c & 0xfc0) >> 6));
            out[3] = static_cast<T>(0x80 | (c & 0x3f));
            out[4] = 0;
        }

        return true;
    }
}
