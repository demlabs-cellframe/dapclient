project(dap-client-c C)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
set (CMAKE_CXX_STANDARD 11)

add_subdirectory(libdap)


include_directories("${INCLUDE_DIRECTORIES} ${dap_core_INCLUDE_DIRS}")
include_directories("${INCLUDE_DIRECTORIES} ${dap_crypto_INCLUDE_DIRS}")
include_directories("${INCLUDE_DIRECTORIES} ${dap_client_INCLUDE_DIRS}")
include_directories("${INCLUDE_DIRECTORIES} ${dap_http_INCLUDE_DIRS}")

add_definitions ("${dap_core_DEFINITIONS}")
add_definitions ("${dap_crypto_DEFINITIONS}")
add_definitions ("${dap_client_DEFINITIONS}")
add_definitions ("${dap_http_DEFINITIONS}")

set(SOURCES sources/client.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
add_executable(${PROJECT_NAME} "sources/client.c" ${HEADERS} ${SOURCES} ${CRYPTO_SRCS})
target_link_libraries(${PROJECT_NAME} dap_crypto  dap_client dap_core dap_http m pthread)