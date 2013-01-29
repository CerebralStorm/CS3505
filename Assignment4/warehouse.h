/* This  class is used to build warehouse objects for a warehouse simulation
 * warehouse class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include<string>

namespace inventory
{
  /* warehouse class for holding elements. */
  class warehouse
  {
  public:
    warehouse(std::string name); //  constructor with parameter
    warehouse(const warehouse& w); // copy constructor

    // leaving the comment below to help me understand friend classes
    //friend class utah_set;  // This allows functions in utah_set to access

    // public methods
    std::string name();

  private:
		std::string name;	    
  };
}

#endif
