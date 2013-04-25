#include <iostream>
#include <sstream>
#include "huge_number.h"

// empty param constructor
huge_number::huge_number()
{
  this->value = "0";
}

// string param constructor
huge_number::huge_number(std::string value)
{
  this->value = value;
}

// copy constructor
huge_number::huge_number(const huge_number& h)
{
  this->value = h.value;
}

// returns the string of the huge_number's value
std::string huge_number::get_value()
{
  return this->value;
}

/* Overriding assignment where lhs is a huge_number, rhs is a huge_number */
huge_number& huge_number::operator=(const huge_number &rhs)
{
  this->value = rhs.value;
  return *this;
}

/* Overriding addition where lhs is a huge_number, rhs is a huge_number */
huge_number huge_number::operator+(const huge_number &rhs)
{
  huge_number h;
  h = add(this->value, rhs.value);
  return h;
}

/* Overriding multiplication where lhs is a huge_number, rhs is a huge_number */
huge_number huge_number::operator*(const huge_number &rhs)
{
  huge_number h;
  h = multiply(this->value, rhs.value);
  return h;
}

/* Overriding subtraction where lhs is a huge_number, rhs is a huge_number */
huge_number huge_number::operator-(const huge_number &rhs)
{
  huge_number h;
  h = subtract(this->value, rhs.value);
  return h;
}

/* Overriding division where lhs is a huge_number, rhs is a huge_number */
huge_number huge_number::operator/(const huge_number &rhs)
{
  huge_number h;
  h = divide(this->value, rhs.value);
  return h;
}

/* Overriding modulus where lhs is a huge_number, rhs is a huge_number */
huge_number huge_number::operator%(const huge_number &rhs)
{
  huge_number h;
  h = mod(this->value, rhs.value);
  return h;
}

/* Adds two numbers stored in strings, building a string result.*/
std::string huge_number::add(std::string a, std::string b)
{
  // Build up a string object to contain the result.  
  std::string result = "";

  // Work right to left.  (Most significant digits to least)  
  int a_pos = a.length() - 1;
  int b_pos = b.length() - 1;  
  int carry = 0;

  // Loop, adding columns, until no more columns and no carry.  
  while (a_pos >= 0 || b_pos >= 0 || carry > 0)
    {
      // Get next digit from each string, or 0 if no more.    
      int a_digit = a_pos >= 0 ? a[a_pos--]-'0' : 0;
      int b_digit = b_pos >= 0 ? b[b_pos--]-'0' : 0;

      /// Calculate the digit for this column and the carry out    
      int sum = a_digit + b_digit + carry;
      carry = sum / 10;
      sum = sum % 10 + '0';

      // Put this column's digit at the start of the result string.    
      result.insert(0, 1, static_cast<char>(sum));
    }

  // Strip any leading 0's  (shouldn't be any, but you'll use this elsewhere.)
  while (result[0] == '0')
    result.erase(0, 1);

  // If the string is empty, it is a 0.  
  if (result.length() == 0)
    result = "0";

  // Return the result.  
  return result;
}

/* Multiplies two numbers stored in strings, building a string result. */
std::string huge_number::multiply(std::string a, std::string b)
{
  std::string result = "0";
  int b_pos = b.length() - 1;

  // Loop once for each digit in b.
  while (b_pos >= 0)
    {
      int b_digit = b[b_pos--]-'0';  // Get next digit from b.

      // Add a to the result the appropriate number of times.      
      for (int i = 0; i < b_digit; i++)
      {
        result = huge_number::add(result, a);
      }

      // Multiply a by 10.      
      a.append("0");
    }

  return result;
}

std::string huge_number::subtract(std::string a, std::string b)
{
  // Build up a string object to contain the result.  
  std::string result = "";

  // Work right to left.  (Most significant digits to least)  
  int a_pos = a.length()-1;
  int b_pos = b.length()-1;  
  bool borrow = false;

  // Loop, adding columns, until no more columns.  
  while (a_pos >= 0 || b_pos >= 0)
    {
      // Get next digit from each string, or 0 if no more.    
      int a_digit = a_pos >= 0 ? a[a_pos--]-'0' : 0;
      int b_digit = b_pos >= 0 ? b[b_pos--]-'0' : 0;      

      //previous column needed to borrow
      if(borrow)
      {
        if(a_digit > 0) // case where nnumber can be borrowed from
        {
          a_digit--;   
          borrow = false;       
        }
        else // case where number can't be borrowed from
        {
          a_digit = 9;
          borrow = true;
        }       
      }

      /// Calculate the digit for this column 
      int diff;   
      if(a_digit >= b_digit)
      {
          diff = a_digit - b_digit;       
      }
      else
      {  
        // if at last position and still need to borrow. Return 0
        if(a_pos == -1)
        {
          return "0";
        }

        borrow = true;
        diff = (a_digit + 10) - b_digit;             
      }

      // Put this column's digit at the start of the result string.    
      result.insert(0, 1, static_cast<char>(diff+'0'));
    }

  // Strip any leading 0's  (shouldn't be any, but you'll use this elsewhere.)
  while (result[0] == '0')
    result.erase(0, 1);

  // If the string is empty, it is a 0.  
  if (result.length() == 0)
    result = "0";

  // Return the result.  
  return result;
}

/* divides two numbers stored in strings, building a string result. */
std::string huge_number::divide(std::string n, std::string d)
{
  // if d is larger than n, in floor division, will result in 0 
  if(huge_number::subtract(n, d) == "0")
  {
    return "0";
  }

  std::string c = "1"; // c is the constant "c = n/d" => "cd = n"
  std::string temp;
  std::string doubler;
  std::string chkDbl;

  // Set our first guess at c
  temp = huge_number::multiply(d, c);

  while(temp != n)
  {

    // if d > n return 0 for floor division
    if(huge_number::subtract(n, temp) == "0")
    {
      return huge_number::subtract(c, "1");
    }

    // try to double c to speed up search times
    doubler = huge_number::multiply(c, "2");
    chkDbl = huge_number::multiply(doubler, d);

    // double c if possible, otherwise increment by 1
    if(huge_number::subtract(n, chkDbl) != "0")
    {
      c = doubler;
    }      
    else 
    {
        c = huge_number::add(c , "1");
    }  
    
    temp = huge_number::multiply(d, c);
  }

  return c;
}

/* divides two numbers stored in strings, building a string result. */
std::string huge_number::mod(std::string n, std::string d)
{
  // if the second number is larger than the first, mod just returns the number
  if(huge_number::subtract(n, d) == "0")
  {
    return n;
  }

  std::string c = "1"; // c is the constant "c = n/d" => "cd = n"
  std::string temp;
  std::string doubler;
  std::string chkDbl;

  // Set our first guess at c
  temp = huge_number::multiply(d, c);  

  // unless we have found c continue
  while(temp != n)
  {
    // if c * d is larger than n, return n - (c-1 * d) which is the remanider 
    if(huge_number::subtract(n, temp) == "0")
    {
      c = huge_number::subtract(c, "1");
      temp = huge_number::multiply(d, c);
      return huge_number::subtract(n, temp);
    }

    // check and see if c can be doubled to speed up iterations
    doubler = huge_number::multiply(c, "2");
    chkDbl = huge_number::multiply(doubler, d);

    // double c if you can, otherwise increment by 1
    if(huge_number::subtract(n, chkDbl) != "0")
    {
      c = doubler;
    }      
    else 
    {
        c = huge_number::add(c , "1");
    }  
    
    // set the next guess for c
    temp = huge_number::multiply(d, c);
  }

  // return 0 if the number is divisable
  return "0";
}
