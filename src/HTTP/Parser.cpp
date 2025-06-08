#include "HTTP/Parser.h"

using namespace server::http;

Request parser::unpack_request(const asio::streambuf &request){
    return Request(Request::Method::HTTP_GET, "/", "HTTP/1.0", {}, "");
}

asio::streambuf parser::pack_response(const Response &response){
    return asio::streambuf();
}
