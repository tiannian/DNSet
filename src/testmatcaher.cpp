#include "matcher.h"

#include <iostream>

using namespace std;

int main() {
    Matcher m;
    m.add("google.com");
    m.add("docs.google.com");
    m.add("baidu.com");
    cout << m.match("test.docs.google.com") << endl;
    return 0;
}
