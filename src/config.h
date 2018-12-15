#ifndef _CONFIG_H
#define _CONFIG_H

#include "uv.h"
#include <vector>
#include <fstream>
#include <string>

namespace dnset {

class Config {
    public:
        Config() = delete;
        Config(std::string path);
        Config(const Config &) = default;
        ~Config() = default;
        void dump();
    private:
        std::ifstream ifs;
        std::string path;
    public:
        struct sockaddr_in bind_addr;
        std::vector<struct sockaddr_in> upstream;
        uint ttl;
        
};

}

#endif