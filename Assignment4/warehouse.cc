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
  /*******************************************************
   * warehouse member function definitions
   ***************************************************** */

  /** Constructor:  Creates a warehouse whose
    *   name is passed in as an argument.
    */
  warehouse::warehouse(std::string name)
  {
    this->name = name;  // This warehouse points to no other warehouse.
  }

  
  /** Destructor:  release any memory allocated
    *   for this object.
    */
  warehouse::~warehouse()
  {

  }

   // returns the string of the huge_number's value
  std::string warehhouse::name()
  {
    return this->name;
  }
}
