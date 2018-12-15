#include "forwarder.h"
#include "string.h"
#include "dnslib/message.h"
#include "dnslib/exception.h"

#include <iostream>

namespace dnset {

void Forwarder::send_cb(uv_udp_send_t* req, int status) {
    std::cout << "data send success " << status << std::endl;
    free(req);
}

void Forwarder::forword_request(uv_udp_t* udp,dns::Message &m, ssize_t nread, const uv_buf_t *bufs, const struct sockaddr *addr) {
    struct sockaddr *paddr = (struct sockaddr*) malloc(sizeof(struct sockaddr));
    memcpy(paddr, addr, sizeof(struct sockaddr));
    auto mid = m.getId();
    for (auto &x: m.mQueries) {
        auto domain = x->getName();
        std::cout << "query a domain name: " << domain << ", message id is " << mid << std::endl;
    }
    if (routeTable.count(mid) == 0) {
        routeTable.insert(std::make_pair(mid,paddr));
    }
    // send to server
    uv_udp_send_t *udp_send = (uv_udp_send_t *)malloc(sizeof(uv_udp_send_t));
    struct sockaddr_in recv_addr;
    uv_ip4_addr("10.0.0.1", 53,&recv_addr);
    uv_buf_t data[] = {uv_buf_init(bufs->base,nread)};
    std::cout << "send data" << std::endl;
    uv_udp_send(udp_send, udp, data, 1, (const struct sockaddr *)&recv_addr, Forwarder::send_cb);
}

void Forwarder::forword_response(uv_udp_t* udp,dns::Message &m, ssize_t nread, const uv_buf_t *bufs) {
    // Qr == 1
    auto mid = m.getId();
    for (auto &x: m.mAnswers) {
        auto domain = x->getName();
        std::cout << "response a domain name: " << domain << ", message id is " << mid << std::endl;
        // match domain
    }
    uv_udp_send_t *udp_send = (uv_udp_send_t *)malloc(sizeof(uv_udp_send_t));
    struct sockaddr *recv_addr = routeTable.at(mid);
    uv_buf_t data[] = {uv_buf_init(bufs->base,nread)};
    uv_udp_send(udp_send, udp, data, 1, (const struct sockaddr *)recv_addr, send_cb);
    free(recv_addr);
}

void Forwarder::alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void Forwarder::recv_cb (uv_udp_t* req, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags) {
    dnset::Forwarder *forwarder = (dnset::Forwarder *)uv_handle_get_data((const uv_handle_t*)req);
    if (nread < 0) {
        std::cout <<  "Read error" << uv_err_name(nread) << std::endl;
        //uv_close((uv_handle_t*) req, NULL);
        free(buf->base);
        return;
    }
    if (nread > 0) {
        char sender[17] = "";
        uv_ip4_name((const struct sockaddr_in*) addr, sender, 16);
        std::cout << "read data " << nread << " bytes."<< std::endl;
        // parse dns message
        dns::Message m;
        try {
            m.decode(buf->base, nread);
        } catch (dns::Exception& e) {
            std::cout << "DNS exception occured when parsing incoming data: " << e.what() << std::endl;
            return;
        }
        if (m.getQr() == 0){
            forwarder->forword_request(req,m,nread,buf,addr);
        } else {
            forwarder->forword_response(req,m,nread,buf);
        }
    }
    free(buf->base);
}


void Forwarder::init() {
    config.dump();
    char host[22] = {0};
    uv_udp_init(loop, &recv_socket);
    uv_handle_set_data((uv_handle_t*)&recv_socket,this);
    uv_udp_bind(&recv_socket, (const struct sockaddr *)&(config.bind_addr), UV_UDP_REUSEADDR);
    uv_udp_recv_start(&recv_socket, Forwarder::alloc_buffer, Forwarder::recv_cb);
    uv_ip4_name(&config.bind_addr,host,21);
    std::cout << "start bind " << host << ":" << config.bind_addr.sin_port << std::endl;
}

}
