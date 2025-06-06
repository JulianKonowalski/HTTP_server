#pragma once

#include <memory>
#include <iostream>

#include <asio/ip/tcp.hpp>
#include <asio/io_context.hpp>

namespace server::core {

/*
 * @brief General purpose TCPSession 
 *  class that handles TCP clients.
 */
class TCPSession : public std::enable_shared_from_this<TCPSession> {

    using tcp = asio::ip::tcp;

public: 


    /* 
     * @brief Creates a new TCPSession
     *  object.
     *
     * @param context I/O context for the 
     *  new session's TCP/IP socket.
     */
    TCPSession(
        asio::io_context& context
    ) : mSocket(context)
    {}

    /*
     * @brief Returns a reference to 
     *  the session's socket.
     *
     * @return A reference to the 
     *  session's TCP/IP socket.
     */
    [[nodiscard]] tcp::socket& get_socket(void) { return mSocket; }

    /*
     * @brief Starts handling the 
     *  client's requests
     */
    virtual void run(void) {
        std::cout << "Starting a new TCP session\n";
    }

protected:

    /*
     * Internal socket connected 
     * to the served client.
     */
    tcp::socket mSocket;

};   

}

