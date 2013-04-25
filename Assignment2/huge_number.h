// Cody Tanner
// u0291987
// CS3505
// Spring 2013

// Header file for huge_number
// huge_number represents integers that are longer than the number of bits the computer can store

#ifndef HUGE_NUMBER_H
#define HUGE_NUMBER_H

#include <string>

class huge_number {
    public:
        huge_number();  // parameterless default constructor
        huge_number(std::string value); //  constructor with parameters
        huge_number(const huge_number& h); // copy constructor

        huge_number & operator=(const huge_number &rhs);    // override =
        huge_number operator+(const huge_number &rhs);      // override +
        huge_number operator-(const huge_number &rhs);      // override -
        huge_number operator*(const huge_number &rhs);      // override *
        huge_number operator/(const huge_number &rhs);      // override /
        huge_number operator%(const huge_number &rhs);      // override %
        std::string get_value();        
  
    private:
        std::string add(std::string a, std::string b);      // helper method for override +
        std::string subtract(std::string a, std::string b); // helper method for override -
        std::string multiply(std::string a, std::string b); // helper method for override *
        std::string divide(std::string n, std::string d);   // helper method for override /
        std::string mod(std::string n, std::string d);      // helper method for override %
        std::string value;
};
#endif