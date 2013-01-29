//
//  request.cc
//  
//
//  Created by Andres Monroy on 1/29/13.
//
//

#include "request.h"
#include <string>

namespace inventory
{
    request::request (int upc, int quantity, std::string warehouse)
    {
        this->upc = upc;
        this->quantity = quantity;
        this->warehouse = warehouse;
    }
    
    int request::get_upc()
    {
        return this->upc;
    }
    
    int request::get_quantity()
    {
        return this->quantity;
    }
    
    std::string request::get_warehouse()
    {
        return this->warehouse;
    }
}