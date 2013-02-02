//
//  warehouse_processor.cc
//  
//
//  Created by Andres Monroy on 2/2/13.
//
//

#include "warehouse_processor.h"
#include <iostream>

namespace inventory
{
    warehouse_processor::warehouse_processor()
    {
    }
    
    /*
     * All warehouses and food_items have been registered. Add each
     * registered food_item with all warehouses and set the start date.
     */
    void warehouse_processor::set_start(date time)
    {
        start = time;
        
        //add the food_items to each warehouse
        register_food_items();
    }
    
    /*
     * Register a warehouse
     */
    void warehouse_processor::add_warehouse(warehouse house)
    {
        //regsiter the warehouse
        warehouses[house.get_name()] = house;
    }
    
    /*
     * Register the existance of a food_item
     */
    void warehouse_processor::add_food_item(food_item item)
    {
        //save the food items to a set to be registered to each
        //warehouse later
        food_items.push_back(item);
    }
    
    /*
     * Let all the warehouses know there is a next day
     */
    void warehouse_processor::process_next()
    {
        //loop through each warehouse and update shelf lives
        for (std::map< std::string, warehouse>::iterator iterator = warehouses.begin(); iterator != warehouses.end(); ++iterator)
        {
            iterator->second.move_to_next_day();
        }
        
        //add one day
        start.add_day();
    }
    
    /*
     * Let the specific warehouse know there is a receive.
     */
    void warehouse_processor::process_receive(receive item)
    {
        warehouses.find(item.get_warehouse())->second.handle_receive(item);
    }
    
    /*
     * Let the specific warehouse know there is a request.
     */
    void warehouse_processor::process_request(request item)
    {
        warehouses.find(item.get_warehouse())->second.handle_request(item);
    }
    
    /*
     * Registers all the food items with each warehouse.
     */
    void warehouse_processor::register_food_items()
    {
        //loop through all warehouses and register each food_item in
        //each warehouse
        for (std::map< std::string, warehouse>::iterator it1 = warehouses.begin(); it1 != warehouses.end(); ++it1)
        {
            //loop through the food_item set and add all food items
            for (std::list<food_item>::iterator it2 = food_items.begin(); it2 != food_items.end(); ++it2)
            {
                it1->second.add_food_item(*it2);
            }
        }
    }
    
    void warehouse_processor::print_report()
    {
        std::cout << "Report by Andres Monroy and Cody Tanner" << "\n\n";
        
        print_out_of_stock();
    }
    
    void warehouse_processor::print_out_of_stock()
    {
        std::cout << "Unstocked Products" << std::endl;
        
        //loop through the warehouses and add all out of stock items from
        //each warehouse to a list
        for (std::map< std::string, warehouse>::iterator iterator = warehouses.begin(); iterator != warehouses.end(); ++iterator)
        {
            warehouse house = iterator->second;
            warehouse_out_of_stock[house.get_name()] = house.out_of_stock_items();
        }
        
        
    }
}
