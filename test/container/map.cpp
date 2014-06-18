#include <peelo/container/map.hpp>
#include <cassert>

int main()
{
    peelo::map<int, bool> container;

    container[1] = false;
    container[3] = true;
    container[6] = false;
    assert(container.size() == 3);
    assert(container.find(3) != container.end());
    assert(container.find(8) == container.end());

    container.clear();
    assert(container.empty());
    assert(container.find(3) == container.end());

    return 0;
}
