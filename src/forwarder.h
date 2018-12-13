#ifndef _FORWARDER_H
#define _FORWARDER_H

#include <map>
#include "uv.h"
#include "dnslib/message.h"

namespace dnset {

class Forwarder {
    public:
        void forword_request(uv_udp_t* udp,dns::Message &m, ssize_t nread, const uv_buf_t *bufs,const struct sockaddr *addr);
        void forword_response(uv_udp_t* udp,dns::Message &m, ssize_t nread, const uv_buf_t *bufs);
        
    private:
        std::map<uint,struct sockaddr *> routeTable;
};

}

#endif