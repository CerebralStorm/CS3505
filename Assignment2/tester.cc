// Cody Tanner
// u0291987
// CS3505
// Spring 2013

#include <iostream>
#include <sstream>
#include <string>
#include "huge_number.h"

using namespace std;

int main ()
{
  huge_number h1("4");
  huge_number h2("30");
  huge_number h3;

  cout << "Addition" << endl;
  cout << "H1: " << h1.get_value() << endl;
  cout << "H2: " << h2.get_value() << endl;
  h3 = h1 + h2; 
  cout << "H3: " << h3.get_value() << endl;
  cout << endl;

  cout << "Multiplication" << endl;
  cout << "H1: " << h1.get_value() << endl;
  cout << "H2: " << h2.get_value() << endl;
  h3 = h1 * h2; 
  cout << "H3: " << h3.get_value() << endl;
  cout << endl;

  cout << "Subtraction" << endl;
  cout << "H2: " << h2.get_value() << endl;
  cout << "H1: " << h1.get_value() << endl;  
  h3 = h2 - h1; 
  cout << "H3: " << h3.get_value() << endl;
  cout << endl;

  cout << "Division" << endl;
  cout << "H2: " << h2.get_value() << endl;
  cout << "H1: " << h1.get_value() << endl;  
  h3 = h2 / h1;
  cout << "H3: " << h3.get_value() << endl;
  cout << endl;

  cout << "Modulus" << endl;
  cout << "H2: " << h2.get_value() << endl;
  cout << "H1: " << h1.get_value() << endl;  
  h3 = h2 % h1;
  cout << "H3: " << h3.get_value() << endl;
  cout << endl;
}

