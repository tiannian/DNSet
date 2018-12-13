#ifndef _FORWARDER_H
#define _FORWARDER_H

#include <map>
#include "uv.h"

class Forwarder {
    public:
        void forword_request();
        void forword_response();
        
    private:
        std::map<uint,std::tuple<sockaddr *,int>> table;
};

#endif