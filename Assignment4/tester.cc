#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <map>
#include <iterator>
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
    typedef inventory::warehouse warehouse;
    map<string, warehouse> warehouses;
    typedef inventory::food_item food_item;
    map<string, food_item> food;
    
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
            food[item.get_upc()] = item;
        }
        else if(command == "Warehouse")
        {
            string ln = line;
            inventory::warehouse wareh = inventory::parser_helper::handle_warehouse(ln); // create warehouse
            warehouses[wareh.get_name()] = wareh;
        }
        else if(command == "Start")
        {
            string ln = line;
        }
        else if(command == "Receive:")
        {
            string word;
            stringstream reader(line);
            string upc;
            string quantity;
            string wh;
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
                    wh = word;
                }
            }

            cout << "Receiving ..." << endl;           
            q = atoi(quantity.c_str());

            cout << "warehouse name: " << warehouses[wh].get_name() << endl;
        }
        else if(command == "Request:")
        {
            string word;
            stringstream reader(line);
            string upc;
            string quantity;
            string wh;
            int q;
        
            //read through the line until until we reach the end
            while (reader.good()){
                reader >> word;
                if (word.compare("Request:") == 0){
                    //read till end of line
                    reader >> word;
                    upc = word;
                    reader >> word;
                    quantity = word;
                    reader >> word;
                    wh = word;
                }

            }

            cout << "Requesting ..." << endl;         
            q = atoi(quantity.c_str());

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
