/* This  class is used to build warehouse objects for a warehouse simulation
 * warehouse class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>
#include <map>
#include <vector>
#include "warehouse.h"
#include "food_item.h"

namespace inventory
{
  warehouse::warehouse(std::string n)
  {
    this->name = n;
    std::map<food_item, int> *i = new std::map<food_item, int>();
    this->inv = *i;
  }

  warehouse::warehouse()
  {
    this->name = "";
    std::map<food_item, int> *i = new std::map<food_item, int>();
    this->inv = *i;
  }

  std::string warehouse::get_name()
  {
    return this->name;
  }
}
