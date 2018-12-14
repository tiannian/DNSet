#include "matcher.h"

#include <iostream>

using namespace std;

int main() {
    dnset::Matcher m;
    m.add("google.com");
    m.add("docs.google.com");
    m.add("baidu.com");
    cout << m.match("test.docs.google.com") << endl;
    cout << m.match("test.abc.google.com") << endl;
    cout << m.match("souhu.com") << endl;
    return 0;
}
