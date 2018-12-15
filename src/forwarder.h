#ifndef _FORWARDER_H
#define _FORWARDER_H

#include <map>
#include "uv.h"
#include "dnslib/message.h"
#include "config.h"
#include <string>

namespace dnset {

class Forwarder {
    public:
        Forwarder() = delete;
        Forwarder(std::string s):loop(uv_default_loop()),config(s) {init();}
        Forwarder(uv_loop_t *loop,std::string s):loop(loop),config(s) {init();}
        Forwarder(const Forwarder &obj) = default;
        ~Forwarder(){uv_loop_close(loop);}
    public:
        
    private:
        void forword_request(uv_udp_t* udp,dns::Message &m, ssize_t nread, const uv_buf_t *bufs,const struct sockaddr *addr);
        void forword_response(uv_udp_t* udp,dns::Message &m, ssize_t nread, const uv_buf_t *bufs);
        void init();
    private:
        static void recv_cb (uv_udp_t* req, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags);
        static void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
        static void send_cb(uv_udp_send_t* req, int status);
    private:
        uv_loop_t *loop;
        Config config;
        std::map<uint,struct sockaddr *> routeTable;
        uv_udp_t recv_socket;
};

}

#endif