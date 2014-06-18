#include <peelo/chrono/date.hpp>
#include <cassert>

int main()
{
    peelo::date d(2006, peelo::month::jan, 15);

    assert(d.day_of_year() == 15);
    assert(!d.is_leap_year());
    assert(d.day_of_week() == peelo::weekday::sun);

    return 0;
}
