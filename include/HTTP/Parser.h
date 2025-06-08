#pragma once

#include <asio/streambuf.hpp>
#include <unordered_map>
#include <filesystem>

#include "http/method.hpp"
#include "http/Request.h"
#include "http/Response.h"

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
server::http::Request unpack_request(asio::streambuf& request_bufer);

/*
 * @brief Parses an HTTPResponse object 
 *  into an std::string object.
 *
 * @param response An HTTPResponse object 
 *  to be parsed.
 *
 * @retu unrn Parsed response in the form
 *  of an std::string object.
 */
asio::streambuf pack_response(const server::http::Response& response);

}
