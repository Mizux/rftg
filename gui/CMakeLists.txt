cmake_minimum_required(VERSION 2.8)

find_package(GTK2 REQUIRED)
include_directories(${GTK2_INCLUDE_DIRS})

file(GLOB_RECURSE _SRCS src *.c)

add_executable(gui ${_SRCS})
target_link_libraries(gui ${GTK2_LIBRARIES} rftg client comm)
