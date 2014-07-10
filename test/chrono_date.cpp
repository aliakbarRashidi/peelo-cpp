#include <peelo/chrono/date.hpp>
#include <cassert>

int main()
{
    peelo::date date(2006, peelo::month::jan, 15);

    assert(date.day_of_year() == 15);
    assert(date.day_of_week() == peelo::weekday::sun);
    assert(!date.is_leap_year());

    return 0;
}
