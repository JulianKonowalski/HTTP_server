#include "core/TCPServer.h"
#include "sessions/PeekSession.h"
#include "HTTP/HTTPSession.h"


static constexpr uint16_t kHTTPPort = 80;

int main(void) {
    server::core::TCPServer<server::sessions::PeekSession> server(kHTTPPort);
    server.run();
}
