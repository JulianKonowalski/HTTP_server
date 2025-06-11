#include "http/Session.h"

#include <chrono>
#include "http/Parser.h"
#include "http/Request.h"
#include "http/Response.h"

using namespace server::http;

char* current_time()
{
  auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  return std::ctime(&time);
}

std::string template_response()
{
    return std::format(R"(<!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Hello</title>
    </head>
    <body>
        <h1> Jest godzina: <br>{}</h1>
    </body>
    </html>)", current_time());
}

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
  std::cout << "Method: " << method_to_str(req.mMethod) << '\n';
  std::cout << "URI: " << req.mURI.string() << '\n';
  std::cout << "HTTP Version: " << req.mHttpVersion << '\n';
  std::cout << "Headers:\n";
  for (const auto& [key, value] : req.mHeaders) {
    std::cout << "  " << key << ": " << value << '\n';
  }
  std::cout << "Body:\n" << req.mBody << '\n';
}


void Session::run(void) {
    do_read();
}

void Session::do_read(void){
    asio::async_read_until(
        mSocket,     
        mBuffer, 
        kMsgEnd, 
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
        Request request = parser::unpack_request(mBuffer);
        print_request(request);
        parser::pack_response( mBuffer,
            Response("HTTP/1.0", 200, "OK", 
            {{"Content-Type", "text/html; charset=UTF-8"},
            {"Content-Length", "100"}}, // should be response length to string
            template_response()));
        do_send(mBuffer);
    }
    catch(const std::exception& e)
    {
        //send error response
        // std::cout << e.what();
    }
}

void Session::do_send(asio::streambuf& response){
    std::string data{
        asio::buffers_begin(response.data()),
        asio::buffers_end(response.data())
    };
    std::cout << data << '\n';
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

void Session::after_send(const asio::error_code &errorCode, const size_t &length){
    if (errorCode) {
        //handle error
    }
}