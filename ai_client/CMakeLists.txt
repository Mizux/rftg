cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE _SRCS src *.c)

add_executable(ai_client ${_SRCS})
target_link_libraries(ai_client comm net)

