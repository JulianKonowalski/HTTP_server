#pragma once

#include <string>
#include <filesystem>

#include "http/method.hpp"


namespace server::http {
  class Request; // Forward declaration
}

namespace server::http::parser {
  // Forward declare the function before it's used as a friend
  server::http::Request unpack_request(asio::streambuf& request_bufer);
}

namespace server::http{    

/*
 * @brief Data container for 
 *  storing information about 
 *  an HTTP request.
 */
class Request {
public:
    using Headers = std::unordered_map<std::string, std::string>;
    /*
     * @brief Creates a new HTTP request
     *  object containing request data.
     *
     * @param method HTTP request method.
     * @param URI URI of the request.
     * @param httpVersion Request's HTTP version.
     * @param headers Request headers.
     * @param body Request body.
     */
    Request(
        const Method& method,
        const std::filesystem::path& URI,
        const std::string& httpVersion,
        const Headers& headers,
        const std::string& body 
    ) : mMethod(method),
        mURI(URI),
        mHttpVersion(httpVersion),
        mHeaders(headers),
        mBody(body)
    {}

    /*
     * @brief Returns the method 
     *  of the request object.
     *
     * @return Const reference to 
     *  the method of the HTTP request.
     */
    const Method& get_method(void) const { return mMethod; }

    /*
     * @brief Returns the URI 
     *  of the request object.
     *
     * @return Const reference to 
     *  the std::filesystem::path 
     *  containing the URI of the 
     *  HTTP request.
     */
    const std::filesystem::path& get_URI(void) const { return mURI; }

    /*
     * @brief Returns the HTTP 
     *  version of the request 
     *  object.
     *
     * @return Const reference 
     *  to a string containing 
     *  the HTTP version of the 
     *  request object.
     */
    const std::string& get_http_version(void) const { return mHttpVersion; }

    /*
     * @brief Returns the headers 
     *  of the request object.
     *
     * @return Const reference to 
     *  an unordered map containing 
     *  headers of the request object.
     */
    const Headers& get_headers(void) const { return mHeaders; }

    /*
     * @brief Returns the body 
     *  of the request object.
     *
     * @return Const reference to 
     *  a string containing the body 
     *  of the request object.
     */
    const std::string& get_body(void) const { return mBody; }

private:
    friend server::http::Request parser::unpack_request(asio::streambuf&);
    Request() = default;

    /* HTTP method of the request */
    /*const*/ Method mMethod;

    /* URI of the request. */
    /*const*/ std::filesystem::path mURI;

    /* Request HTTP version */
    /*const*/ std::string mHttpVersion;

    /* 
     * Unordered map containing
     * headers of the request.
     */
    /*const*/ Headers mHeaders;

    /*
     * A string containing 
     * the body of the request.
     */
    /*const*/ std::string mBody;

};   

}

