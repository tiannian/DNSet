#include "matcher.h"

#include <iostream>

namespace dnset {

void Matcher::add(std::string p) {
    patten.insert(p);
}

void Matcher::del(std::string p) {
    auto fr = patten.find(p);
    if (fr != patten.end()) {
        patten.erase(fr);
    }
}

bool Matcher::has(std::string p) {
    return patten.count(p) == 1;
}

std::string& trim(std::string &s) {  
    if (s.empty()) {  
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}  

bool Matcher::match(std::string p) {
    auto domain = trim(p);
    if ("" == domain) {
        return false;
    }
    while (domain != "") {
        std::cout << domain << std::endl;
        if (patten.count(domain) == 1) {
            return true;
        } else {
            auto pos = domain.find(".");
	    if (pos == std::string::npos) {
                return false;
            }
            domain = domain.substr(pos+1);
        }
    }
    return false;
}

}
