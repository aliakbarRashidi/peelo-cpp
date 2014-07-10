#include <peelo/text/stringbuilder.hpp>
#include <cassert>

int main()
{
    peelo::stringbuilder sb("foo bar baz");

    assert(sb.length() == 11);

    sb.clear();
    assert(sb.empty());

    sb.append("bar");
    assert(sb.equals("bar"));

    sb.prepend("foo");
    assert(sb.length() == 6);
    assert(sb.equals("foobar"));

    return 0;
}
