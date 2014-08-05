#include <peelo/chrono/date.hpp>
#include <cassert>

int main()
{
    peelo::duration duration = peelo::date::today() - peelo::date::yesterday();

    assert(duration.days() == 1);

    return 0;
}
