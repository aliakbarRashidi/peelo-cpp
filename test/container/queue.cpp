#include <peelo/container/queue.hpp>
#include <cassert>

int main()
{
    peelo::queue<int> queue;

    queue << 1 << 2 << 3;
    assert(queue.size() == 3);
    assert(queue.front() == 1);
    assert(queue.back() == 3);

    queue.pop();
    assert(queue.size() == 2);
    assert(queue.front() == 2);
    assert(queue.back() == 3);

    return 0;
}
