#include "core/TCPHandler.h"
#include "core/TCPServer.h"

static constexpr uint16_t kHTTPPort = 80;

int main(void) {
    server::core::TCPServer<server::core::TCPHandler> server(kHTTPPort);
    server.run();
}
