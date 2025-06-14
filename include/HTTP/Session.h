#pragma once

#include <memory>

#include <asio/streambuf.hpp>
#include <asio/placeholders.hpp>
#include <asio/read_until.hpp>
#include <asio/write.hpp>

#include "core/TCPSession.h"

namespace server::http {

/*
 * @brief TCP session for serving
 *  HTTP requests
 */
class Session : 
    public core::TCPSession,
    public std::enable_shared_from_this<Session> 
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
     * @see Session::mBuffer
     */
    void do_read(void);

    /*
     * @brief wites to buffer and calls after 
     *
     * @see Session::mBuffer
     */
    void do_send(asio::streambuf& response);

    /*
     * @brief Validates and handles 
     *  the received HTTP request.
     *
     * @see Session::do_read()
     * @see Session::mBuffer
     */
    void after_read(const asio::error_code& errorCode, const size_t& length);

    /*
     * @brief Sends a response 
     *  to the HTTP client.
     */
    void after_send(const asio::error_code& errorCode, const size_t& length);


private:

    /*
     * Internal buffer containing 
     * the received HTTP request.
     */
    asio::streambuf mBuffer;
};

}
