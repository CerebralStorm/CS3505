/* This  class is used to build warehouse objects for a warehouse simulation
 * warehouse class
 *
 * Cody Tanner
 * u0291987
 * January, 2013
 */

#include "warehouse.h"

namespace inventory
{
    warehouse::warehouse()
    {
        this->name = "";
    }
    
    warehouse::warehouse(std::string n)
    {
        this->name = n;
    }
    
    warehouse::warehouse(const warehouse& other)
    {
        this->name = "";
        inv = std::map< std::string, food_item >();
        
        *this = other;
    }
    
    const warehouse& warehouse::operator= (const warehouse& rhs)
    {
        if (this == &rhs)
            return *this;
        
        this->name = rhs.get_name();
        this->inv = rhs.inv;
        
        return *this;
    }
    
    bool warehouse::operator <(const warehouse& rhs) const
    {
        return this->name < rhs.get_name();
    }

    
    /*
     * Registers a food_item in this warehouse
     */
    void warehouse::add_food_item(food_item item)
    {
        //add unique food items to the map
        //this will keep track of all possible food items in this warehouse
        inv[item.get_upc()] = item;
    }
    
    /*
     * Alerts the warehouse of a move to the next day, and update the shelf
     * lives of each food_item
     */
    void warehouse::move_to_next_day()
    {
        //loop through each food item in the warehouse and remove 1 day
        //from the shelf life
        for (std::map< std::string, food_item>::iterator iterator = inv.begin(); iterator != inv.end(); ++iterator)
        {
            iterator->second.next_day();
        }
    }
    
    /*
     * Adds the food_items to the warehouse inventory
     */
    void warehouse::handle_receive(receive item)
    {
        //find item and receive the quantity
        inv.find(item.get_upc())->second.receive_items(item.get_quantity());
    }
    
    /*
     * Removes food_items to the warehouse inventory
     */
    void warehouse::handle_request(request item)
    {
        //find item and remove the quantity
        inv.find(item.get_upc())->second.request_items(item.get_quantity());
    }
    
    /*
     * Return a list of all out of stock items
     */
    std::list<std::string> warehouse::out_of_stock_items()
    {
        std::list<std::string> out_of_stock;
        //loop through and add any out of stock items to the list
        for (std::map< std::string, food_item>::iterator iterator = inv.begin(); iterator != inv.end(); ++iterator)
        {
            food_item item = iterator->second;
            //if the item is empty, add the upc to the list
            if (item.is_empty()){
                out_of_stock.push_back(item.get_upc());
            }
        }
        
        return out_of_stock;
    }
    
    /*
     * Returns a list of stocked items
     */
    std::list<std::string> warehouse::fully_stocked_items()
    {
        std::list<std::string> stocked;
        //loop through and add any out of stock items to the list
        for (std::map< std::string, food_item>::iterator iterator = inv.begin(); iterator != inv.end(); ++iterator)
        {
            food_item item = iterator->second;
            //if the item is empty, add the upc to the list
            if (!item.is_empty()){
                stocked.push_back(item.get_upc());
            }
        }
        
        return stocked;
    }
    
    std::string warehouse::get_name() const
    {
        return name;
    }

}
