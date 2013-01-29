//
//  request.h
//  
//
//  Created by Andres Monroy on 1/29/13.
//
//

#ifndef _request_h
#define _request_h

#include<string>

namespace inventory
{
    class request
    {
    public:
        request(int upc, int quantity, std::string warehouse);
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
