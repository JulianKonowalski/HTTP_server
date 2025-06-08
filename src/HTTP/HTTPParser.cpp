#include "HTTP/HTTPParser.h"

using namespace server::http;

HTTPRequest parser::string_to_request(
    const asio::basic_streambuf<>& request
) {
    return HTTPRequest();
}

std::string response_to_string(
    const HTTPResponse& response
) {
    return std::string();
}
