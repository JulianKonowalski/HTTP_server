#include "core/TCPServer.h"
#include "HTTP/Session.h"

static constexpr uint16_t kHTTPPort = 80;

int main(void) {
    server::core::TCPServer<server::http::Session> server(kHTTPPort);
    server.run();
}
