namespace peelo
{
    static inline std::size_t utf8_size(char c)
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
}
