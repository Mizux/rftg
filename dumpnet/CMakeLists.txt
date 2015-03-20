cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE _SRCS src *.c)

add_executable(dumpnet ${_SRCS})
target_link_libraries(dumpnet net)

