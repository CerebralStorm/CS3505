/* This  class is used to build warehouse objects for a warehouse simulation
 * warehouse class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>
#include "warehouse.h"

namespace inventory
{
  warehouse::warehouse(std::string n)
  {
    this->name = n;
  }

  std::string warehouse::get_name()
  {
    return this->name;
  }
}
