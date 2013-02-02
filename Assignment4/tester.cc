#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include "warehouse.h"
#include "food_item.h"
#include "date.h"
#include "parser_helper.h"

using namespace std;

string first_word(const string& line);
inventory::warehouse * get_warehouse(string s, vector<inventory::warehouse> warehouses);
inventory::food_item get_food(string upc, vector<inventory::food_item> food);

int main(int argc, char* argv[])
{
    string file_name = argv[1];
    ifstream inv_file("data1.txt");
    string line;
    string command;
    vector<inventory::warehouse> warehouses;
    vector<inventory::food_item> food;

    
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
            food.push_back(item); // add food item to map
        }
        else if(command == "Warehouse")
        {
            string ln = line;
            inventory::warehouse item = inventory::parser_helper::handle_warehouse(ln); // create warehouse
            warehouses.push_back(item); // add warehouse to map
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
            inventory::warehouse *w = get_warehouse(wh, warehouses);
            inventory::food_item f = get_food(upc, food);            
            q = atoi(quantity.c_str());

            for(int i = 0; i < q; i++)
            {  
                inventory::warehouse temp = *w;
                temp.inv.push_back(f);                
            }    

            cout << wh << " added " << q << " " << f.get_name() << endl;
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


// Helper method returns a pointer to the warehouse whose name matches the passed in string
inventory::warehouse * get_warehouse(string s, vector<inventory::warehouse> warehouses) 
{
    vector<inventory::warehouse>::iterator it;

    for (it = warehouses.begin(); it < warehouses.end(); it++)
    {
        if(it->get_name() == s)
        {
            return &(*it);
        } 
    }

    return 0;
}

// Helper method returns a food item of the passed in upc
inventory::food_item get_food(string upc, vector<inventory::food_item> food) 
{
    vector<inventory::food_item>::iterator it;

    for (it = food.begin(); it < food.end(); it++)
    {
        if(it->get_upc() == upc)
        {
            return *it;
        } 
    }
}
