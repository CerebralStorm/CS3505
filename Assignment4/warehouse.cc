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
    std::vector<food_item> *v = new std::vector<food_item>();
    this->inv = *v;
  }

  std::string warehouse::get_name()
  {
    return this->name;
  }
}
