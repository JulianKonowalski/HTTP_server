cmake_minimum_required(VERSION 3.0.0)
project(server)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

SET(ASIO_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/asio/asio/include
)

add_executable(server 
    src/main.cpp
 "include/sessions/HTTPSession.h")

target_include_directories(
    server
    PUBLIC
    ${ASIO_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (WIN32)
    target_compile_definitions(server PRIVATE _WIN32_WINNT=0x0601)
endif()
target_compile_definitions(server PRIVATE ASIO_STANDALONE)

include_directories(include)
