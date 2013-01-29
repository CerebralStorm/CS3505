// Write a command-line application that determines if an integer is prime.  
// The program should behave as follows:

//     The program is launched from the command line with a single argument.
//     The program prints 'prime' if the argument can be parsed as a integer that is prime, otherwise the program prints 'composite'.

// Terminate the output with a newline character.  Your program is not required to correctly test parameters that specify an integer 
// that does not fit within the int datatype.  Resolve user errors in a user-friendly way.

// Written by: Cody Tanner
// u0291987
// CS3505

// This program is an implementation of the above specification. It takes an int argument from the
// command line and displays weither is prime or composite

#include <iostream>  
#include <cstdlib>
#include <cmath>

using namespace std;

int main (int argc, char *argv[])
{
  int num = atoi(argv[1]); // try to convert the command line arg to an int
  
  if (num <= 1)
  {
    cout << "A number must be greater than 1 to be a composite or prime number" << endl;
    return 0;
  }
  else if (num == 2)
  {
    cout << "Prime" << endl;
    return 0;
  }

  bool prime = true; 
  for(int i = 2; i < num; i++) // check all the numbers up to num and see if any are a divisor
  {
      if(num % i == 0)
        prime = false;
  }
  if (prime)
  {
    cout << "Prime" << endl;  
  }
  else
  {
    cout << "Composite" << endl;
  }
}
  