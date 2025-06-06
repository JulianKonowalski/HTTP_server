#pragma once

#include <memory>
#include <cstdint>
#include <iostream>

#include <asio/ip/tcp.hpp>
#include <asio/io_context.hpp>
#include <asio/placeholders.hpp>

#include "core/TCPSession.h"

#ifndef DERIVED_CONCEPT
    #define DERIVED_CONCEPT
    template<class T, class U>
    concept Derived = std::is_base_of<U, T>::value;
#endif

namespace server::core {

/*
 * @brief General purpose 
 *  TCP/IP server that listens 
 *  to connection requests on 
 *  a given port and asynchronously 
 *  serves clients.
 *
 * @tparam tSession TCP session object
 *  containing the client handling 
 *  logic.
 *
 * @see tSession
 */
template<Derived<TCPSession> tSession>
class TCPServer {
public:

    /*
     * @brief Constructs a new 
     *  server object.
     *
     * @param port Port that the 
     *  server's acceptor socket 
     *  will listen on for connection 
     *  requests.
     */
    TCPServer(const uint16_t& port);

    /*
     * @brief Starts listening 
     *  for client requests. After 
     *  receiving a request accepts 
     *  it and delegates it to a 
     *  dedicated session object.
     */
    void run(void);


private:

    using tcp = asio::ip::tcp;

    /*
     * @brief Awaits and accepts 
     *  new connections asynchronously.
     *  After accepting a connection 
     *  delegates it for validation to 
     *  the internal handle_accept method.
     *
     * @see TCPServer::handle_accept()
     */
    void accept_connections(void);
    
    /*
     * @brief Checks if there are 
     *  no socket errors after receiving 
     *  a request and delegates the 
     *  request to a dedicated session 
     *  object.
     *
     * @see tSession
     */
    void handle_accept(std::shared_ptr<tSession> session, const std::error_code& errorCode);

    /*
     * @brief Handles connection 
     *  errors.
     *
     * @param errorCode Error code.
     */
    void handle_error(const std::error_code& errorCode);

    /* Server's I/O context */
    asio::io_context mContext;

    /* Internal acceptor socket */
    tcp::acceptor mAcceptor;

};

template<Derived<TCPSession> tSession>
TCPServer<tSession>::TCPServer(const uint16_t& port) :
    mAcceptor(mContext, tcp::endpoint(tcp::v4(), port))
{}

template<Derived<TCPSession> tSession>
void TCPServer<tSession>::run(void) {
    this->accept_connections();
    mContext.run();
}

template<Derived<TCPSession> tSession>
void TCPServer<tSession>::accept_connections(void) {
    auto newSession = std::shared_ptr<tSession>(new tSession(mContext));
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

template<Derived<TCPSession> tSession>
void TCPServer<tSession>::handle_accept (
    std::shared_ptr<tSession> session, 
    const std::error_code& errorCode
) {
    if (errorCode) { this->handle_error(errorCode); } 
    else { session->run(); }
    this->accept_connections(); //this is not recursive, it's asynchronous
}

template<Derived<TCPSession> tSession>
void TCPServer<tSession>::handle_error (
    const std::error_code& errorCode
) {
    std::cout << "Server encountered an error: " 
        << errorCode.message() 
        << std::endl;    

    //log to file or whatever
}

}
