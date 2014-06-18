#include <peelo/memory/ptr.hpp>
#include <cassert>

int main()
{
    peelo::ptr<int> p(new int(5));

    assert(!!p);
    assert(p.use_count() == 1);

    p.reset();
    assert(!p);

    return 0;
}
