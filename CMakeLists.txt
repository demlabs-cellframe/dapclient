project(dap-client-c C)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
set(CMAKE_C_STANDARD 11)

add_subdirectory(libdap)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS src/*.h)

add_executable(${PROJECT_NAME} client.c ${HEADERS} ${SOURCES})
target_include_directories(dap-client-c PRIVATE src)

target_link_libraries(${PROJECT_NAME} dap_crypto dap_core pthread curl)
