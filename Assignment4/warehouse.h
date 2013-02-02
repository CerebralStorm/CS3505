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
#include <vector> 
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
    std::vector<food_item> inv; 

    bool operator <(const warehouse& rhs) const
    {
      return name < rhs.name;
    }

  private:
    std::string name;          
  };
}

#endif
