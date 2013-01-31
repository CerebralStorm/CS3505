#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "warehouse.h"
#include "food_item.h"
#include "date.h"
#include "parser_helper.h"

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
          
        getline(inv_file, line);
        command = first_word(line);
          
        if(command == "FoodItem")
        {
            string ln = line;
            inventory::food_item item = inventory::parser_helper::handle_food_item(ln);
            
            cout << "FoodItem" << endl;
            cout << item.get_upc() << endl;
            cout << item.get_shelf_life() << endl;
            cout << item.get_name() << "\n\n";
        }
        else if(command == "Warehouse")
        {
            string ln = line;
            inventory::warehouse item = inventory::parser_helper::handle_warehouse(ln);
            
            cout << "Warehouse" << endl;
            cout << item.get_name() << "\n\n";
        }
        else if(command == "Start")
        {
            string ln = line;
            inventory::parser_helper::handle_date(ln);
        }
        else if(command == "Receive:")
        {
            string ln = line;
            
            cout << "Receive" << endl;
        }
        else if(command == "Request:")
        {
            string ln = line;
            
            cout << "Request" << endl;
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