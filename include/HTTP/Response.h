#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

namespace server::http {
  
/*
 * @brief Data container for
 *  storing information about
 *  an HTTP response.
 */
class Response {
public:
    using Headers = std::unordered_map<std::string, std::string>;

    /*
     * @brief Creates a new HTTP Response 
     *  object containing response data.
     */
    Response(
        const std::string& httpVersion,
        const uint16_t& responseCode,
        const std::string& reasonPhrase,
        const Headers& headers,
        const std::string& body 
    ) : mHttpVersion(httpVersion),
        mResponseCode(responseCode),
        mReasonPhrase(reasonPhrase),
        mHeaders(headers),
        mBody(body)
    {}

    /*
     * @brief Returns the HTTP version 
     *  of the response.
     *
     * @return Const reference to a
     *  string containing the response 
     *  HTTP version.
     */
    const std::string& get_http_version(void) { return mHttpVersion; }

    /*
     * @brief Returns the response 
     *  code.
     *
     * @return Const reference to 
     *  the response code.
     */
    const uint16_t& get_response_code(void) { return mResponseCode; }

    /*
     * @brief Returns the response 
     *  reason phrase.
     *
     * @return Const reference to a
     *  string containing the response 
     *  reason phrase.
     */
    const std::string& get_reason_phrase(void) { return mReasonPhrase; }

    /*
     * @brief Returns the response 
     *  headers.
     *
     * @return Const reference to 
     *  an unordered map of the 
     *  response headers.
     */
    const Headers& get_headers(void) { return mHeaders; }

    /*
     * @brief Returns the response 
     *  body
     *
     * @return Const reference to a 
     *  string containing the response 
     *  body.
     */
    const std::string& get_body(void) { return mBody; }

private:

    /*
     * A string containing response 
     * HTTP version.
     */
    const std::string mHttpVersion;

    /*
     * Response code.
     */
    const uint16_t mResponseCode;

    /*
     * A string containing response 
     * reason phrase.
     */
    const std::string mReasonPhrase;

    /*
     * An unordered map containing
     * response headers.
     */
    const Headers mHeaders;

    /*
     * A string containing response 
     * body.
     */
    const std::string mBody;

};

}
