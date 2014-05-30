#include <peelo/container/pair.hpp>
#include <cassert>

int main()
{
    peelo::pair<int, int> pair(1, 2);

    assert(pair.first() == 1);
    assert(pair.second() == 2);

    return 0;
}
