#pragma once
#include <stdexcept>

#include <asio/streambuf.hpp>

#include "http/Request.h"
#include "http/Response.h"

static constexpr char kMsgEnd[] = "\r\n\r\n";

namespace server::http::parser {

/*
 * @brief Exception object exclusive 
 *  to the HTTP parser functionality.
 */
class ParserException : public std::runtime_error {
public:

    /*
     * @brief Creates a ParserException 
     *  object with the default error 
     *  message.
     */
    ParserException(void) throw();

    /*
     * @brief Creates a ParserException
     *  object with the supplied error 
     *  message.
     *
     * @param message Error message to 
     *  be displayed.
     */
    ParserException(char const* const message) throw();

};

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
Request unpack_request(asio::streambuf& requestBufer);

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
void pack_response(asio::streambuf& outputBufer, const Response& response);


}
