#include "tree.h"
#include <vector>
#include <string>

using namespace std;
using namespace dnset;

int main () {
    Tree<string> t;
    vector<string> arg1 = {"hello", "world", "1"};
    t.addNode(arg1);
    t.dump();
    return 0;
}
