//
//  receive.h
//  
//
//  Created by Andres Monroy on 1/29/13.
//
//

#ifndef _receive_h
#define _receive_h

#include <string>

namespace inventory
{
    class receive
    {
    public:
        receive(int upc, int quantity, std::string warehouse);
        int get_upc();
        int get_quantity();
        std::string get_warehouse();
        
    private:
        int upc;
        int quantity;
        std::string warehouse;
    };
}

#endif
