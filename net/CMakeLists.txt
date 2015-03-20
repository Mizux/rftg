cmake_minimum_required(VERSION 2.8)

link_libraries(m)

file(GLOB_RECURSE _HDRS include *.h)
file(GLOB_RECURSE _SRCS src *.c)

add_library(net ${_HDRS} ${_SRCS})
target_include_directories(net PUBLIC "include")
