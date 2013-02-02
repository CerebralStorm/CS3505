/* This  class is used to build food_item objects for a warehouse simulation
 * food_item class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>
#include "food_item.h"

namespace inventory
{
  food_item::food_item(std::string u, int s, std::string n)
  {
    this->upc = u;
    this->shelf_life = s;
    this->name = n;
  }

  food_item::food_item()
  {
    this->upc = "";
    this->shelf_life = 0;
    this->name = "";
  }

  std::string food_item::get_upc()
  {
    return this->upc;
  }

  int food_item::get_shelf_life()
  {
    return this->shelf_life;
  }

  std::string food_item::get_name()
  {
    return this->name;
  }
}
