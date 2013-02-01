#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <map>
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
    typedef map<string, inventory::food_item> food_map;
    food_map food;
    map<string, inventory::warehouse> warehouse;
    food_map iter = food.begin();
    
    if (inv_file.is_open())
    {
      while ( inv_file.good() )
      {
          
        getline(inv_file, line);
        command = first_word(line);
          
        if(command == "FoodItem")
        {
            string ln = line;
            inventory::food_item item = inventory::parser_helper::handle_food_item(ln); // create food item
            food.insert(pair<string,inventory::food_item>(item.get_upc(), item)); // add food item to map
        }
        else if(command == "Warehouse")
        {
            string ln = line;
            inventory::warehouse item = inventory::parser_helper::handle_warehouse(ln); // create warehouse
            warehouse.insert(pair<string,inventory::warehouse>(item.get_name(), item)); // add warehouse to map
        }
        else if(command == "Start")
        {
            string ln = line;
            inventory::parser_helper::handle_date(ln);
        }
        else if(command == "Receive:")
        {
            string word;
            stringstream reader(line);
            string upc;
            string quantity;
            string wareH;
            int q;
        
            //read through the line until until we reach the end
            while (reader.good()){
                reader >> word;
                if (word.compare("Receive:") == 0){
                    //read till end of line
                    reader >> word;
                    upc = word;
                    reader >> word;
                    quantity = word;
                    reader >> word;
                    wareH = word;
                }

            }

            //inventory::food_item f = new inventory::food_item(food[upc].get_upc(), food[upc].get_shelf_life(), food[upc].get_name());
            //inventory::warehouse WH = warehouse[wareH];
            
            // find will return an iterator to the matching element if it is found
            // or to the end of the map if the key is not found
            iter = food.find(upc);
            if (iter != food.end() ) 
                std::cout << "Value is: " << iter->second << '\n';
            else
                std::cout << "Key is not in my_map" << '\n';

            q = atoi(quantity.c_str());
            for(int i = 0; i < q; i++)
            {
                cout << i << ",";
            }
            
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