#pragma once

#include <memory>
#include <asio/ip/tcp.hpp>
#include <asio/io_context.hpp>

namespace server::core {

/*
 * @brief general purpose TCPSession class
 *  that handles TCP clients.
 *
 * @tparam handler tcpSessionHandler client 
 *  handling logic. The object will follow 
 *  given instructions to allow for easy
 *  customisation of client handling logic.
 */
template <typename tHandler>
class TCPSession : public std::enable_shared_from_this<TCPSession<tHandler>> {

    using tcp = asio::ip::tcp;

public: 

    /* 
     * @brief creates a new TCPSession
     *  object from a given I/O context
     *
     * @param context asio::io_context 
     *  I/O context for the new TCPSession 
     *  object
     */
    TCPSession(asio::io_context& context) :
        mSocket(context) 
    {}

    /*
     * @brief returns a reference to 
     *  the session socket 
     *
     * @return asio::ip::tcp::socket 
     *  reference to the session socket
     */
    tcp::socket& get_socket(void) { return mSocket; }

    /*
     * @brief starts handling the client.
     *  The instructions don't loop unless 
     *  the handler contains a main loop.
     */
    void run(void) {
        mHandler();
    }

private:
    tHandler mHandler;
    tcp::socket mSocket;

};   

}

