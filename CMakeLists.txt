cmake_minimum_required(VERSION 3.0)
if(TARGET dap_client)
    return() # The project has already been built.
endif()
project(dap_client C)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
set(CMAKE_C_STANDARD 11)

add_subdirectory(libdap)

file(GLOB SOURCES src/*.c)
file(GLOB HEADERS src/*.h)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} INTERFACE src)
target_link_libraries(${PROJECT_NAME} dap_crypto dap_core pthread curl)

