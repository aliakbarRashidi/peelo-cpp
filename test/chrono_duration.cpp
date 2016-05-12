#include <peelo/chrono/date.hpp>
#include <cassert>

int main()
{
  const peelo::duration duration = peelo::date::today() - peelo::date::yesterday();

  assert(duration.days() == 1);
  assert(duration.seconds() == peelo::duration::seconds_per_day);

  return 0;
}
