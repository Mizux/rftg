cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE _HDRS include *.h)
file(GLOB_RECURSE _SRCS src *.c)

add_library(comm ${_HDRS} ${_SRCS})
target_link_libraries(comm rftg)
target_include_directories(comm PUBLIC "include")
