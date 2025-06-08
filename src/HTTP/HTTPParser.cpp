#include "HTTP/HTTPParser.h"

using namespace server::http;

HTTPRequest parser::unpack_request(const asio::streambuf &request){
    return HTTPRequest();
}

asio::streambuf parser::pack_response(const HTTPResponse &response){
    return asio::streambuf();
}
