// Write a command-line application that converts pounds to kilograms for the user.  
// The program should behave as follows:

//     The program is launched from the command line without arguments.
//     The user is prompted to enter a weight in pounds.
//     The user enters a number (possibly decimal).
//     The program treats the number as a weight in pounds, converts it to kilograms, and outputs the result for the user.
//     The program ends, and the user is returned to the command line.

// Round the result to two decimal places.  (It is not required to display two digits to the right of the decimal point.)  
// Use cout and cin for console I/O.  Resolve user errors in a user-friendly way.

// Written by: Cody Tanner
// u0291987
// CS3505

// This program is an implementation of the above specification. It takes a positive number from the user
// and converts it to kilograms to 2 decimal places

#include <iostream>  
#include <cstdlib>
#include <cmath>

using namespace std;

int main ()
{
  double pounds = 0;

  do
  {
    cout << "Enter a weight in Pounds: ";
    cin >> pounds; // get weight from the user

    if(pounds < 0)
    {
      cout << "Weight must be entered as a positive number." << endl;
    }

  } while(pounds < 0); // ensure the user entered a positive number

  double kilograms = (pounds/2.20462); // convert the weight to kilograms
  int whole = kilograms; // extract the whole number portion of the calculation
  double decimalPlace = kilograms - whole; // exctract the decimal portion of the calculation
  int decimal = decimalPlace*100; // convert the decimal to a whole number of 2 digits
  cout << pounds << " pounds in kilograms is: ";
  cout << whole << "." << decimal << endl;  // display the calculation
}