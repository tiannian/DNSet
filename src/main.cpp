#include "uv.h"
#include <iostream>
#include "dnslib/message.h"
#include "dnslib/exception.h"
#include "forwarder.h"

using namespace std;

static void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void recv_cb (uv_udp_t* req, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags) {
    dnset::Forwarder *forwarder = (dnset::Forwarder *)uv_handle_get_data((const uv_handle_t*)req);
    if (nread < 0) {
        cout <<  "Read error" << uv_err_name(nread) << endl;
        //uv_close((uv_handle_t*) req, NULL);
        free(buf->base);
        return;
    }
    if (nread > 0) {
        char sender[17] = "";
        uv_ip4_name((const struct sockaddr_in*) addr, sender, 16);
        cout << "read data " << nread << " bytes."<< endl;
        // parse dns message
        dns::Message m;
        try {
            m.decode(buf->base, nread);
        } catch (dns::Exception& e) {
            cout << "DNS exception occured when parsing incoming data: " << e.what() << endl;
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

int main(int argc, char* argv[]) {
    
    // command parse
    
    dnset::Forwarder forwarder;
    
    uv_loop_t *loop = uv_default_loop();
    uv_udp_t recv_socket;
    uv_handle_set_data((uv_handle_t*)&recv_socket,&forwarder);
    uv_udp_init(loop, &recv_socket);
    struct sockaddr_in recv_addr;
    
    uv_ip4_addr("0.0.0.0", 15353,&recv_addr);
    uv_udp_bind(&recv_socket, (const struct sockaddr *)&recv_addr, UV_UDP_REUSEADDR);
    uv_udp_recv_start(&recv_socket, alloc_buffer, recv_cb);
    
    cout << "start bind 0.0.0.0:5353" << endl;
    return uv_run(loop, UV_RUN_DEFAULT);
}
