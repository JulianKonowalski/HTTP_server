#pragma once

#include <asio/basic_streambuf.hpp>

#include "HTTP/HTTPRequest.h"
#include "HTTP/HTTPResponse.h"

namespace server::http::parser {

/*
 * @brief Parses a string containing
 *  an HTTP request and returns an 
 *  HTTPRequest object.
 *
 * @param request A string containing 
 *  the HTTP request to be parsed.
 *
 * @return Parsed request in the form 
 *  of an HTTPRequest object.
 */
HTTPRequest string_to_request(const asio::basic_streambuf<>& request);

/*
 * @brief Parses an HTTPResponse object 
 *  into an std::string object.
 *
 * @param response An HTTPResponse object 
 *  to be parsed.
 *
 * @return Parsed response in the form
 *  of an std::string object.
 */
std::string response_to_string(const HTTPResponse& response);

}
