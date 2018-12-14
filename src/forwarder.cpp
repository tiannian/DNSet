#include "forwarder.h"
#include "string.h"

#include <iostream>

namespace dnset {

static void send_cb(uv_udp_send_t* req, int status) {
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
    uv_udp_send(udp_send, udp, data, 1, (const struct sockaddr *)&recv_addr, send_cb);
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

}
