#include <peelo/container/range.hpp>
#include <cassert>

int main()
{
    peelo::range<int> range(1, 3);
    int counter = 1;

    assert(range.front() == 1);
    assert(range.back() == 3);

    for (peelo::range<int>::iterator i = range.begin(); i != range.end(); ++i)
    {
        assert(*i++ == counter++);
    }

    return 0;
}
