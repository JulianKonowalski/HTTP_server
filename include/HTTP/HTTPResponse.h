#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

namespace server::http {
  
class HTTPResponse {
public:

    using Headers = std::unordered_map<std::string, std::string>;

    HTTPResponse(
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

    const std::string& get_http_version(void) { return mHttpVersion; }
    const uint16_t& get_response_code(void) { return mResponseCode; }
    const std::string& get_reason_phrase(void) { return mReasonPhrase; }
    const Headers& get_headers(void) { return mHeaders; }
    const std::string& get_body(void) { return mBody; }

private:

    const std::string mHttpVersion;
    const uint16_t mResponseCode;
    const std::string mReasonPhrase;
    const Headers mHeaders;
    const std::string mBody;

};

}
