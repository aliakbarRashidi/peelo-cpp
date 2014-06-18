#include <peelo/container/array.hpp>
#include <cassert>

int main()
{
    peelo::array<int, 3> array;

    assert(array.size() == 3);

    array[0] = 1;
    array[1] = 2;
    array[2] = 3;

    assert(array.front() == 1);
    assert(array.back() == 3);

    ++array.back();

    assert(array.back() == 4);

    return 0;
}
