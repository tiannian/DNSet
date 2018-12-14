#include "matcher.h"

void Matcher::add(std::string p) {
    patten.insert(p);
}

void Matcher::del(std::string p) {
    auto fr = patten.find(p);
    if (fr != patten.end()) {
        patten.earse(fr);
    }
}

bool Matcher::has(std::string p) {
    return patten.count(p) == 1;
}

vector<string> split(const string& str,const string& delim) { //将分割后的子字符串存储在vector中
    vector<string> res;
    if("" == str) return  res;
    string strs = str + delim;
    size_t pos;
    size_t size = strs.size();

    for (int i = 0; i < size; ++i) {
        pos = strs.find(delim, i);
        if( pos < size) {
            string s = strs.substr(i, pos - i);
            res.push_back(s);
            i = pos + delim.size() - 1;
        }
    }
    return res;	
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
    vector<std::string> res;
    auto domain = trim(p);
    if ("" == domain) {
        return false;
    }
    while (domain == "") {
        std::cout << domain << std::endl;
        if (patten.count(domain) == 1) {
            return true;
        } else {
            domain = domain.substr(domain.find("."));
        }
    }
    return false;
}