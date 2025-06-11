#include "http/Parser.h"

#include <iostream>

using namespace server::http;

parser::ParserException::ParserException(void) throw() 
    : std::runtime_error("Encountered an unknown error while parsing an HTTP message.")
{}

parser::ParserException::ParserException(char const* const message) throw() 
    : std::runtime_error(message) 
{}

Request parser::unpack_request(asio::streambuf &request_bufer){
    Request request;
    std::istream is(&request_bufer);
    std::string line;
    if (std::getline(is, line)){
        std::istringstream iss(line);
        std::string method_str, uri_str;
        iss >> method_str >> uri_str >> request.mHttpVersion;
        request.mMethod = str_to_method.at(method_str);
        request.mURI = uri_str;
    } else {
        throw parser::ParserException("Empty HTTP request.");
    }
    std::cout<<"parser\n";
    while (std::getline(is, line)) {
        if (line.empty() || line == "\r") {
            break;
        }
        std::istringstream line_stream(line);
        std::string key, value;
        if (std::getline(line_stream, key, ':')) {
            if (std::getline(line_stream, value)) {
                size_t start = value.find_first_not_of(" \t");
                if (start != std::string::npos) {
                    value = value.substr(start);
                } else {
                    value.clear();
                }
                request.mHeaders[key] = value;
            }
        }
    }
    std::string body{
      std::istreambuf_iterator<char>(is),
      std::istreambuf_iterator<char>()
    };
    request.mBody = std::move(body);
    return request;
}

asio::streambuf parser::pack_response(const Response &response)
{
    return asio::streambuf();
}
