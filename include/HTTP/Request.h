#pragma once

#include <string>
#include <filesystem>

namespace server::http{  

/*
 * @brief Available HTTP 
 *  request methods.
 */
enum class Method {
    HTTP_GET,
    HTTP_HEAD,
    HTTP_OPTIONS,
    HTTP_TRACE,
    HTTP_PUT,
    HTTP_DELETE, //DELETE is a windows macro, so don't change this
    HTTP_POST,
    HTTP_PATCH,
    HTTP_CONNECT
};

/*
 * @brief Data container for 
 *  storing information about 
 *  an HTTP request.
 */
struct Request {
    using Headers = std::unordered_map<std::string, std::string>;

    /* HTTP method of the request */
    Method mMethod;

    /* URI of the request. */
    std::filesystem::path mURI;

    /* Request HTTP version */
    std::string mHttpVersion;

    /* 
     * Unordered map containing
     * headers of the request.
     */
    Headers mHeaders;

    /*
     * A string containing 
     * the body of the request.
     */
    std::string mBody;

};

}

