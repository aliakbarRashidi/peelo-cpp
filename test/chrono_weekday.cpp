#include <peelo/chrono/weekday.hpp>
#include <cassert>
#include <sstream>

int main()
{
  assert(static_cast<int>(peelo::weekday::mon) == 1);
  assert(peelo::weekday::mon + 3 == peelo::weekday::thu);
  assert(peelo::weekday::sat - 2 == peelo::weekday::thu);
  assert(peelo::weekday::mon + 8 == peelo::weekday::tue);
  assert(peelo::weekday::sat - 8 == peelo::weekday::fri);

  std::stringstream ss;
  ss << peelo::weekday::mon;
  assert(ss.str() == "Monday");
  ss.str(std::string());
  ss << peelo::weekday::fri;
  assert(ss.str() == "Friday");

  return 0;
}
