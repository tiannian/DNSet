#include "config.h"

#include <iostream>

#include "utils.h"

namespace dnset {

Config::Config(std::string path) {
    if (path.empty()) {
        std::cerr << "Config file can't be empty." << std::endl;
        exit(1);
    }
    ifs.open(path);
    if (!ifs.is_open()) {
        std::cerr << "Config file can't open." << std::endl;
        exit(1);
    }
    this->path = path;
    std::string s;
    while(std::getline(ifs,s)) {
        s = trim(s);
        if (s[0] == '#' || s.empty()) {
            continue;
        }
        auto r = split(s);
        if (r[0] == "listen") {
            auto ns = split(r[1],':');
            if (ns.size() == 1) {
                uv_ip4_addr(ns[0].c_str(),53,&bind_addr);
            } else {
                std::cout << ns[0] << ":" << ns[1] << std::endl;
                uv_ip4_addr(ns[0].c_str(),stoi(ns[1]),&bind_addr);
            }
        } else if (r[0] == "ttl") {
            ttl = stoi(r[1]);
        } else if (r[0] == "nameserver") {
            auto ns = split(r[1],':');
            struct sockaddr_in addr;
            if (ns.size() == 1) {
                uv_ip4_addr(ns[0].c_str(),53,&addr);
            } else {
                std::cout << ns[0] << ":" << ns[1] << std::endl;
                uv_ip4_addr(ns[0].c_str(),stoi(ns[1]),&addr);
            }
            upstream.push_back(addr);
        }
    }
}

void Config::dump() {
    char host[17] = {0};
    uv_ip4_name(&bind_addr,host,16);
    std::cout << "bind_addr:" << host << ":" << bind_addr.sin_port << std::endl;
    for (auto &x: upstream) {
        uv_ip4_name(&x,host,16);
        std::cout << "upstreams:" << host << ":" << x.sin_port << std::endl;
    }
    std::cout << "ttl:" << ttl << std::endl;
}

}