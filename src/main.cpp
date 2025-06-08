#include "core/TCPServer.h"
#include "HTTP/Session.h"
#include "sessions/PeekSession.h"

static constexpr uint16_t kHTTPPort = 80;

int main(void) {
    // server::core::TCPServer<server::sessions::PeekSession> server(kHTTPPort);
    server::core::TCPServer<server::http::Session> server(kHTTPPort);
    server.run();
}
