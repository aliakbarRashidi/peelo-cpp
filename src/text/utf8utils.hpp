namespace peelo
{
    static inline std::size_t utf8_decode_size(int c)
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

    template< class CharT, class Traits >
    static inline bool utf8_decode(std::basic_ios<CharT, Traits>& is,
                                   rune::value_type& result)
    {
        int c = is.rdbuf()->sbumpc();
        std::size_t size;

        if (c == Traits::eof())
        {
            return false;
        }
        switch ((size = utf8_decode_size(c)))
        {
            case 0:
                is.setstate(std::basic_ios<CharT, Traits>::failbit);

                return false;

            case 1:
                result = c;
                break;

            case 2:
                result = c & 0x1f;
                break;

            case 3:
                result = c & 0x0f;
                break;

            case 4:
                result = c & 0x07;
                break;

            case 5:
                result = c & 0x03;
                break;

            default:
                result = c & 0x01;
        }
        for (std::size_t i = 1; i < size; ++i)
        {
            if ((c = is.rdbuf()->sbumpc()) == Traits::eof())
            {
                return false;
            }
            else if ((c & 0xc0) != 0x80)
            {
                is.setstate(std::basic_ios<CharT, Traits>::failbit);

                return false;
            }
            result = (result << 6) | (c & 0x3f);
        }

        return true;
    }

    static inline bool utf8_decode(std::wistream& is, rune::value_type& result)
    {
        typedef std::wistream::traits_type traits;
        const traits::int_type eof = traits::eof();
        std::basic_streambuf<wchar_t, traits>* b = is.rdbuf();
        int c1;
        int c2;

        if (static_cast<traits::int_type>(c1 = b->sbumpc()) == eof
            || static_cast<traits::int_type>(c2 = b->sbumpc()) == eof)
        {
            return false;
        }
        else if (c1 >= 0xd8 && c1 <= 0xdb)
        {
            int c3;
            int c4;

            if (static_cast<traits::int_type>(c3 = b->sbumpc()) == eof
                || static_cast<traits::int_type>(c4 = b->sbumpc()) == eof)
            {
                return false;
            }
            result = static_cast<rune::value_type>(
                ((((c2 - 0xd8) << 2) + ((c1 & 0xc0) >> 6) + 1) << 16)
                + ((((c1 & 0x3f) << 2) + (c4 - 0xdc)) << 8)
                + c3
            );
        } else {
            result = static_cast<rune::value_type>(c2 * 256 + c1);
        }

        return true;
    }

    template< typename T >
    static inline bool utf8_encode(T* out,
                                   std::streamsize& size,
                                   rune::value_type c)
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
            size = 1;
        }
        else if (c < 0x800)
        {
            out[0] = static_cast<T>(0xc0 | ((c & 0x7c0) >> 6));
            out[1] = static_cast<T>(0x80 | (c & 0x3f));
            size = 2;
        }
        else if (c < 0x10000)
        {
            out[0] = static_cast<T>(0xe0 | ((c & 0xf000) >> 12));
            out[1] = static_cast<T>(0x80 | ((c & 0xfc0) >> 6));
            out[2] = static_cast<T>(0x80 | (c & 0x3f));
            size = 3;
        } else {
            out[0] = static_cast<T>(0xf0 | ((c & 0x1c0000) >> 18));
            out[1] = static_cast<T>(0x80 | ((c & 0x3f000) >> 12));
            out[2] = static_cast<T>(0x80 | ((c & 0xfc0) >> 6));
            out[3] = static_cast<T>(0x80 | (c & 0x3f));
            size = 4;
        }

        return true;
    }

    static inline bool utf16_encode(wchar_t* out,
                                    std::streamsize& size,
                                    rune::value_type c)
    {
        if (c > rune::max.code()
            || (c & 0xfffe) == 0xfffe
            || (c >= 0xd800 && c <= 0xdfff)
            || (c >= 0xffd0 && c <= 0xfdef))
        {
            return false;
        }
        else if (c > 0xffff)
        {
            out[0] = static_cast<wchar_t>(0xd800 + (c >> 10));
            out[1] = static_cast<wchar_t>(0xdc00 + (c & 0x3ff));
            size = 2;
        } else {
            out[0] = static_cast<wchar_t>(c);
            size = 1;
        }

        return true;
    }
}
