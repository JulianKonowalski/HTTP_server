#include "http/Session.h"

#include "http/Parser.h"
#include "http/Request.h"
#include "http/Response.h"

using namespace server::http;


#include <iostream>
void print_request(const server::http::Request& req) {
  auto method_to_str = [](Method m) -> const char* {
    switch (m) {
      case Method::HTTP_GET: return "GET";
      case Method::HTTP_HEAD: return "HEAD";
      case Method::HTTP_OPTIONS: return "OPTIONS";
      case Method::HTTP_TRACE: return "TRACE";
      case Method::HTTP_PUT: return "PUT";
      case Method::HTTP_DELETE: return "DELETE";
      case Method::HTTP_POST: return "POST";
      case Method::HTTP_PATCH: return "PATCH";
      case Method::HTTP_CONNECT: return "CONNECT";
      default: return "UNKNOWN";
    }
  };
  std::cout << "Method: " << method_to_str(req.get_method()) << '\n';
  std::cout << "URI: " << req.get_URI().string() << '\n';
  std::cout << "HTTP Version: " << req.get_http_version() << '\n';
  std::cout << "Headers:\n";
  for (const auto& [key, value] : req.get_headers()) {
    std::cout << "  " << key << ": " << value << '\n';
  }
  std::cout << "Body:\n" << req.get_body() << '\n';
}


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

void Session::after_read(const asio::error_code& errorCode, const size_t& length){
    try
    {
    if (errorCode) {
        //error response
        // throw;
    }
        Request request = server::http::parser::unpack_request(mBuffer);
        print_request(request);
        asio::streambuf response = parser::pack_response(Response("HTTP/1.0", 200, "OK", {}, ""));
        //do_send(response);
    }
    catch(const std::exception& e)
    {
        //send error response
        // std::cout << e.what();
    }
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

void server::http::Session::after_send(const asio::error_code &errorCode, const size_t &length){
    if (errorCode) {
        //handle error
    }
}
