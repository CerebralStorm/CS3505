/* This  class is used to build food_item objects for a warehouse simulation
 * food_item class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#ifndef FOOD_ITEM_H
#define FOOD_ITEM_H

#include <string>

namespace inventory
{
  class food_item
  {
  public:
    food_item(std::string upc, int shelf_life, std::string name);
    food_item();

    // public methods
    std::string get_upc();
    int get_shelf_life();
    std::string get_name();

    bool operator <(const food_item& rhs) const
    {
      return shelf_life < rhs.shelf_life;
    }

  private:
    std::string upc;
    int shelf_life;
    std::string name;     
  };
}

#endif