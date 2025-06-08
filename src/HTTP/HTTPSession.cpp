#include "HTTP/HTTPSession.h"

using namespace server::http;


void HTTPSession::run(void) {
    do_read();
    //read header //async
    //check for socket error
    //parse header
    //check for parse error
    //interpret header
    //fetch data
    //make response
    //send response //async
}

void HTTPSession::do_read(void){
    asio::async_read_until(
    mSocket,     
    mBuffer, 
    "\r\n\r\n", 
    std::bind(
        &HTTPSession::after_read,
        shared_from_this(),
        asio::placeholders::error,
        asio::placeholders::bytes_transferred
        )
    );
}

void HTTPSession::do_send(asio::streambuf& response){
    asio::async_write(
    mSocket,
    response,
    std::bind(
        &HTTPSession::after_send,
        shared_from_this(),
        asio::placeholders::error,
        asio::placeholders::bytes_transferred
        )
    );
}



void HTTPSession::after_read(const asio::error_code& errorCode, const size_t& length){
    try
    {
    if (errorCode) {
        //error response
        // throw;
    }
        HTTPRequest request = server::http::parser::unpack_request(mBuffer);
        asio::streambuf response = parser::pack_response(HTTPResponse());
        do_send(response);
    }
    catch(const std::exception& e)
    {
        //send error response
    }
}

void server::http::HTTPSession::after_send(const asio::error_code &errorCode, const size_t &length){
    if (errorCode) {
        //handle error
    }
    run();
}
