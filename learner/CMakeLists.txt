cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE _SRCS src *.c)

add_executable(learner ${_SRCS})
target_link_libraries(learner rftg)

