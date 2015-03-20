cmake_minimum_required(VERSION 2.8)

find_package(GTK2 REQUIRED)
include_directories(${GTK2_INCLUDE_DIRS})

file(GLOB_RECURSE _HDRS include *.h)
file(GLOB_RECURSE _SRCS src *.c)

add_library(client ${_HDRS} ${_SRCS})
target_link_libraries(client ${GTK2_LIBRARIES} rftg comm)
target_include_directories(client PUBLIC "include")
