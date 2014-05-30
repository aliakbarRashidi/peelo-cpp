#include <peelo/container/vector.hpp>
#include <cassert>

int main()
{
    peelo::vector<int> vector;

    vector << 1 << 2 << 3;
    assert(vector.size() == 3);
    assert(vector.back() == 3);

    vector.pop_back();
    assert(vector.size() == 2);
    assert(vector.back() == 2);

    return 0;
}
