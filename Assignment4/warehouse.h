/* This  class is used to build warehouse objects for a warehouse simulation
 * warehouse class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <map> 
#include "food_item.h"

namespace inventory
{
  class warehouse
  {

  public:
    warehouse(std::string name);
    warehouse();

    // public methods
    std::string get_name();

    // member varibales
    std::map<food_item, int> inv;

    bool operator <(const warehouse& rhs) const
    {
      return name < rhs.name;
    }

  private:
    std::string name;          
  };
}

#endif
