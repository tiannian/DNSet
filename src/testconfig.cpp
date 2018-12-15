#include <iostream>

#include "config.h"

using namespace std;

int main() {
    dnset::Config c("../etc/dnset.conf");
    c.dump();
    return 0;
}