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
            string word;
            stringstream reader(line);
            string upc;
            string shelf_life;
            string name;
        
            //read through the line until until we reach the end
            while (reader.good()){
                reader >> word;
                if (word.compare("Code:") == 0){
                    //read one more word to get the upc code
                    reader >> word;
                    upc = word;
                }
                else if(word.compare("life:") == 0){
                    reader >> word;
                    shelf_life = word;
                }
                else if(word.compare("Name:") == 0){
                    //read in the rest of the line
                    while(reader >> word){
                        //reader >> word;
                        name += word + " ";
                    }
                }
            }

            food[upc] = food_item(upc, atoi(shelf_life.c_str()), name);
        }
        else if(command == "Warehouse")
        {
            string word;
            stringstream reader(line);
            string name;
            
            //read through the line until until we reach the end
            while (reader.good()){
                reader >> word;
                if (word.compare("-") == 0){
                    //read one more word to get the upc code
                    reader >> word;
                    name = word;
                }
            }
        
            warehouses[name] = warehouse(name);
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
          
            q = atoi(quantity.c_str());
            food_item f = food[upc];
            warehouses[wh].inv[f] = q;  
            cout <<  warehouses[wh].inv[f] << " = " << q << endl;
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

            q = atoi(quantity.c_str());
            food_item f = food[upc];

            cout <<  warehouses[wh].inv[f];    
            
            int amount = warehouses[wh].inv[f] - q;
            if (amount < 0)
            {
                amount = 0;
            }
            warehouses[wh].inv[f] = amount;

            cout << " = " << amount << endl;

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
