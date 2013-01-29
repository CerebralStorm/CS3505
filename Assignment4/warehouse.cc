/* This  class is used to build warehouse objects for a warehouse simulation
 * warehouse class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>

namespace inventory
{
  class warehouse
  {
  public:
    warehouse(std::string name);

    // public methods
    std::string get_name();

  private:
    std::string name;     
  };

  /*******************************************************
   * warehouse member function definitions
   ***************************************************** */

  /** Constructor:  Creates a warehouse whose
    *   name is passed in as an argument.
    */
  warehouse::warehouse(std::string n)
  {
    this->name = n;
  }

  std::string warehouse::get_name()
  {
    return this->name;
  }
}
