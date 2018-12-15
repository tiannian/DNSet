#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <sstream>
#include <vector>

std::string& trim(std::string &s) {
    if (s.empty()) {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

std::vector<std::string> split(const std::string& s,const char flag = ' ') {
    std::vector<std::string> sv;
    std::istringstream iss(s);
    std::string temp;
    while (getline(iss, temp, flag)) {
        sv.push_back(temp);
    }
    return sv;
}

#endif