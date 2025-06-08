#pragma once

#include <asio/streambuf.hpp>

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
HTTPRequest unpack_request(const asio::streambuf& request);

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
asio::streambuf pack_response(const HTTPResponse& response);

}
