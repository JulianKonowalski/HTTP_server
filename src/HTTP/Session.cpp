#include "HTTP/Session.h"

#include "HTTP/Parser.h"
#include "HTTP/Request.h"
#include "HTTP/Response.h"

using namespace server::http;


void Session::run(void) {
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

void Session::do_read(void){
    asio::async_read_until(
    mSocket,     
    mBuffer, 
    "\r\n\r\n", 
    std::bind(
        &Session::after_read,
        shared_from_this(),
        asio::placeholders::error,
        asio::placeholders::bytes_transferred
        )
    );
}

void Session::do_send(asio::streambuf& response){
    asio::async_write(
    mSocket,
    response,
    std::bind(
        &Session::after_send,
        shared_from_this(),
        asio::placeholders::error,
        asio::placeholders::bytes_transferred
        )
    );
}



void Session::after_read(const asio::error_code& errorCode, const size_t& length){
    try
    {
    if (errorCode) {
        //error response
        // throw;
    }
        Request request = server::http::parser::unpack_request(mBuffer);
        asio::streambuf response = parser::pack_response(Response("HTTP/1.0", 200, "OK", {}, ""));
        do_send(response);
    }
    catch(const std::exception& e)
    {
        //send error response
    }
}

void server::http::Session::after_send(const asio::error_code &errorCode, const size_t &length){
    if (errorCode) {
        //handle error
    }
    run();
}
