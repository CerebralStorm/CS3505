/* This  class is used to build food_item objects for a warehouse simulation
 * food_item class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#ifndef DATE_H
#define DATE_H

#include<string>

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
}

#endif
