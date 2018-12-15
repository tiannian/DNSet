#include "matcher.h"

#include <iostream>

#include "utils.h"

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
