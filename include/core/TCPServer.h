#pragma once

#include <memory>
#include <cstdint>
#include <iostream>

#include <asio/ip/tcp.hpp>
#include <asio/io_context.hpp>
#include <asio/placeholders.hpp>

#include "core/TCPSession.h"

namespace server::core {

/*
 * @brief general purpose 
 *  TCP/IP server that listens 
 *  to connection requests on 
 *  a given port and asynchronously 
 *  serves clients 
 */
template<typename tHandler>
class TCPServer {
public:

    /*
     * @brief constructs a new 
     *  server object
     *
     * @param port uint16_t port 
     *  that the server's acceptor 
     *  will listen on
     */
    TCPServer(uint16_t port);

    /*
     * @brief starts listening 
     *  for client requests. After 
     *  receiving a request accepts 
     *  it and delegates it to a 
     *  dedicated session object
     */
    void run(void);


private:

    using tcp = asio::ip::tcp;

    /*
     * @brief awaits and accepts 
     *  new connections asynchronously 
     */
    void accept_connections(void);
    
    /*
     * @brief checks if there are 
     *  no socket errors after receiving 
     *  a request and delegates the 
     *  request to a dedicated session 
     *  object
     */
    void handle_accept(std::shared_ptr<TCPSession<tHandler>> session, const std::error_code& errorCode);

    asio::io_context mContext;
    tcp::acceptor mAcceptor;

};

template<typename tHandler>
TCPServer<tHandler>::TCPServer(uint16_t port) :
    mAcceptor(mContext, tcp::endpoint(tcp::v4(), port))
{
    std::cout << "Created a server\n";
}

template<typename tHandler>
void TCPServer<tHandler>::run(void) {
    std::cout << "Starting server\n";
    this->accept_connections();
    mContext.run();
}

template<typename tHandler>
void TCPServer<tHandler>::accept_connections(void){
    auto newSession = std::shared_ptr<TCPSession<tHandler>>(new TCPSession<tHandler>(mContext));
    mAcceptor.async_accept(
        newSession->get_socket(),
        std::bind(
            &TCPServer::handle_accept, 
            this, 
            newSession, 
            asio::placeholders::error
        )
    );
}

template<typename tHandler>
void TCPServer<tHandler>::handle_accept(
        std::shared_ptr<TCPSession<tHandler>> session, 
        const std::error_code& errorCode
) {
    if (!errorCode) { session->run(); }
    else { std::cout << "Encountered an error: " << errorCode.message() << "\n"; }
    this->accept_connections(); //this is not recursive, it's asynchronous
}

}
