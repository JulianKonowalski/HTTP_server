#pragma once
#include <unordered_map>
#include <string>

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

inline const  std::unordered_map
<std::string, Method> str_to_method{
        {"GET",Method::HTTP_GET},
        {"HEAD",Method::HTTP_HEAD},
        {"OPTIONS",Method::HTTP_OPTIONS},
        {"TRACE",Method::HTTP_TRACE},
        {"PUT",Method::HTTP_PUT},
        {"DELETE",Method::HTTP_DELETE},
        {"POST",Method::HTTP_POST},
        {"PATCH",Method::HTTP_PATCH},
        {"CONNECT",Method::HTTP_CONNECT},
};

}