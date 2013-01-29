#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "warehouse.h"
#include "food_item.h"
#include "date.h"

using namespace std;

string first_word(const string& line);

int main(int argc, char* argv[])
{
    string file_name = argv[1];
    ifstream inv_file("data1.txt");
    string line;
    string command;

    if (inv_file.is_open())
    {
      while ( inv_file.good() )
      {
        getline (inv_file,line);
        command = first_word(line);

        if(command == "FoodItem")
        {
          string upc = line.substr(21, 10);
          string shelf_life = line.substr(45, 1);
          cout << upc << endl;
          cout << shelf_life << endl;
        }
        else if(command == "Warehouse")
        {
          //cout << "Recognized Warehouse" << endl;
        }
        else if(command == "Start")
        {
          //cout << "Recognized Start Date" << endl;
        }
        else if(command == "Receive:")
        {
          //cout << "Recognized Receive" << endl;
        }
        else if(command == "Request:")
        {
          //cout << "Recognized Request" << endl;
        }
        else if(command == "Next")
        {
          //cout << "Recognized Next Day" << endl;
        }

      }
      inv_file.close();
    }
  return 0;
}

string first_word(const string& line)
{
    return line.substr(0, line.find(' '));
}