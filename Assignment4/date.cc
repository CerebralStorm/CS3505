/* This  class is used to build date objects for a warehouse simulation
 * date class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>
#include "date.h"

namespace inventory
{
  date::date(int m, int d, int y)
  {
    this->month = m;
    this->day = d;
    this->year = y; 
  }

  int date::get_month()
  {
    return this->month;
  }

  int date::get_day()
  {
    return this->day;
  }

  int date::get_year()
  {
    return this->year;
  }
}
