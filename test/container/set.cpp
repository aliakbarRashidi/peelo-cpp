#include <peelo/container/set.hpp>
#include <cassert>

int main()
{
    peelo::set<int> container;

    container << 2 << 3 << 6;
    assert(container.size() == 3);
    assert(container.count(3) == 1);

    container.erase(6);
    assert(container.size() == 2);
    assert(container.count(6) == 0);

    container.clear();
    assert(container.empty());
    assert(container.count(3) == 0);

    return 0;
}
