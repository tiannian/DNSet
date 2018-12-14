#include "tree.h"
#include <vector>
#include <string>

using namespace std;
using namespace dnset;

int main () {
    Tree<string> t;
    vector<string> arg1 = {"hello", "Alice", "1"};
    t.addNode(arg1);
    vector<string> arg2 = {"hello", "Bob", "1"};
    t.addNode(arg2);
    vector<string> arg3 = {"hello", "Carlo", "1"};
    t.addNode(arg3);
    t.dump();
    return 0;
}
