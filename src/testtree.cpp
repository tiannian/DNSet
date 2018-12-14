#include "tree.h"
#include <vector>

using namespace std;

int main () {
    Tree t;
    vector arg1 = {"hello", "world", "1"}
    t.add(arg1);
    t.dump();
    return 0;
}