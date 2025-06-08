#pragma once

#include <memory>

#include <asio/basic_streambuf.hpp>

#include "core/TCPSession.h"

namespace server::sessions {
 
/*
 * @brief TCP session for serving
 *  HTTP requests
 */
class HTTPSession : 
    public core::TCPSession,
    public std::enable_shared_from_this<HTTPSession> 
{
public:

    using core::TCPSession::TCPSession;

    /*
     * @brief Starts serving 
     *  a HTTP client.
     */
    void run(void) override;

    /*
     * @brief Reads HTTP request 
     *  header into an internal
     *  buffer.
     *
     * @see HTTPSession::mBuffer
     */
    void do_read(void);

    /*
     * @brief Validates and handles 
     *  the received HTTP request.
     *
     * @see HTTPSession::do_read()
     * @see HTTPSession::mBuffer
     */
    void handle_request(void);

    /*
     * @brief Sends a response 
     *  to the HTTP client.
     */
    void do_send(void);

private:

    /*
     * Internal buffer containing 
     * the received HTTP request.
     */
    asio::basic_streambuf<> mBuffer;

};

}
