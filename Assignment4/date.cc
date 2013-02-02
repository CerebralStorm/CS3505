/* This  class is used to build date objects for a warehouse simulation
 * date class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>
#include <sstream>
#include "date.h"

namespace inventory
{
  date::date(int m, int d, int y)
  {
    static int length[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
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

  std::string date::get_date()
  {
    int i = this->month;
    int j = this->day;
    int k = this->year;
    std::string m = date::convertInt(i);
    std::string d = date::convertInt(j);
    std::string y = date::convertInt(k);
    return m + "/" + d + "/" + y;
  }

  std::string date::convertInt(int number)
  {
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
  }
}
