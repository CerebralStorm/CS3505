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
#include <vector> 
#include "food_item.h"

namespace inventory
{
  class warehouse
  {

  public:
    warehouse(std::string name);

    // public methods
    std::string get_name();
    std::vector<food_item> get_inv();
    
    //std::map<std::string, food_item::food_item> inv;

  private:
    std::string name;
    std::vector<food_item> inv;           
  };
}

#endif
