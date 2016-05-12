#include <peelo/chrono/month.hpp>
#include <cassert>
#include <sstream>

int main()
{
  assert(static_cast<int>(peelo::month::jan) == 1);
  assert(peelo::month::jan + 3 == peelo::month::apr);
  assert(peelo::month::sep - 2 == peelo::month::jul);
  assert(peelo::month::jan + 13 == peelo::month::feb);
  assert(peelo::month::nov - 13 == peelo::month::oct);

  std::stringstream ss;
  ss << peelo::month::jan;
  assert(ss.str() == "January");
  ss.str(std::string());
  ss << peelo::month::oct;
  assert(ss.str() == "October");

  return 0;
}
