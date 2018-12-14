#ifndef _MATCHER_H
#define _MATCHER_H

#include <set>
#include <string>

namespace dnset {
    
class Matcher {
    public:
        Matcher() = default;
        Matcher(const Matcher &) = default;
        ~Matcher() = default;
        
    public:
        void add(std::string p);
        void del(std::string p);
        bool has(std::string p);
        
    public:
        bool match(std::string p);

    private:
        std::set<std::string> patten;
};
    
}

#endif