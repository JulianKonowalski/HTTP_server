#pragma once

#include <memory>

#include <asio/placeholders.hpp>
#include <asio/error_code.hpp>

#include "core/TCPSession.h"

namespace server::sessions {

/*
 * @brief TCP/IP session that
 *  synchronously reads data 
 *  sent from the client and 
 *  outputs it to the console 
 *  window.
 */
class PeekSession : 
    public server::core::TCPSession,
    public std::enable_shared_from_this<PeekSession> 
{
public:

    using core::TCPSession::TCPSession;

    /*
     * @brief Starts handling a 
     *  TCP client.
     */
    void run(void) override {
        this->do_read();
    }

private:

    /*
     * @brief Asynchronously reads 
     *  available data from the session 
     *  socket. After reading invokes 
     *  a handle_read method that handles 
     *  received data.
     */
    void do_read(void) {
        auto self = shared_from_this();
        mSocket.async_read_some(
            asio::buffer(mBuffer),
            std::bind(
                &PeekSession::handle_read,
                self,
                asio::placeholders::error,
                asio::placeholders::bytes_transferred
            )
        );
    }

    /*
     * @brief Handles data read from 
     *  the session socket. After 
     *  handling the data buffer invokes 
     *  do_read method to continue reading 
     *  bytes from the socket.
     *
     * @param self Shared pointer to *this*
     *  to avoid premature session termination
     * @param errorCode Socket error code, 0
     *  if no error has occured
     * @param length Length of the received 
     *  data buffer.
     */
    void handle_read(
        const asio::error_code& errorCode, 
        const size_t& length
    ) {
        if (!errorCode) {
            std::cout.write(this->mBuffer.data(), length);
        } else if (errorCode == asio::error::eof) {
            return; 
        }
        this->do_read();
    }
    
    /*
     * Internal data buffer for 
     * bytes read from the socket.
     */
    std::array<char, 1024> mBuffer;

};

}
