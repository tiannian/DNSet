#include "uv.h"
#include <iostream>
#include "forwarder.h"

using namespace std;

int main(int argc, char* argv[]) {
    uv_loop_t *loop = uv_default_loop();
    dnset::Forwarder f(loop,"../etc/dnset.conf");
    
    return uv_run(loop, UV_RUN_DEFAULT);
    //return 0;
}
