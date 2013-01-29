/* This  class is used to build date objects for a warehouse simulation
 * date class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>

namespace inventory
{
  class date
  {
  public:
    date(int month, int day, int year); //  constructor with parameter

    // public methods
    int get_month();
    int get_day();
    int get_year();

  private:
    int month;
    int day;
    int year;     
  };

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
