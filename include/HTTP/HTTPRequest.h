#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>

namespace server::http {
 
class HTTPRequest {
public:

    using Headers = std::unordered_map<std::string, std::string>;

    enum class Method {
        GET,
        HEAD,
        OPTIONS,
        TRACE,
        PUT,
        DELETE,
        POST,
        PATCH,
        CONNECT
    };

    HTTPRequest(
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

    const Method& get_method(void) { return mMethod; }
    const std::filesystem::path& get_URI(void) { return mURI; }
    const std::string& get_http_version(void) { return mHttpVersion; }
    const Headers& get_headers(void) { return mHeaders; }
    const std::string& get_body(void) { return mBody; }

private:

    const Method mMethod;
    const std::filesystem::path mURI;
    const std::string mHttpVersion;
    const Headers mHeaders;
    const std::string mBody;

};   

}

