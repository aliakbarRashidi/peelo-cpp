#include <peelo/container/stack.hpp>
#include <cassert>

int main()
{
    peelo::stack<int> stack;

    stack << 1 << 2 << 3;
    assert(stack.size() == 3);
    assert(stack.top() == 3);

    stack.pop();
    assert(stack.size() == 2);
    assert(stack.top() == 2);

    return 0;
}
