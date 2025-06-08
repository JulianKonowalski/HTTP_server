#pragma once

#include <string>
#include <unordered_map>

namespace server::http {
 
class HTTPRequest {
public:

private:
    std::unordered_map<std::string, std::string> mData;
};   

}

