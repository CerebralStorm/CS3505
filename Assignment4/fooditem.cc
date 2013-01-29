/* This  class is used to build food_item objects for a warehouse simulation
 * food_item class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include <string>

namespace inventory
{
  class food_item
  {
  public:
    food_item(int upc, int shelf_life, std::string name); 

    // public methods
    int get_upc();
    int get_shelf_life();
    std::string get_name();

  private:
    int upc;
    int shelf_life;
    std::string name;     
  };

  /*******************************************************
   * food_item member function definitions
   ***************************************************** */

  /** Constructor:  Creates a food_item */
  food_item::food_item(int u, int s, std::string n)
  {
    this->upc = u;
    this->shelf_life = s;
    this->name = n;
  }

  int food_item::get_upc()
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
