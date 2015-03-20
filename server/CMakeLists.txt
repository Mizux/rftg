cmake_minimum_required(VERSION 2.8)

# Find MySQL
find_package(MYSQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIRS})
# Find pthread
find_package (Threads REQUIRED)

file(GLOB_RECURSE _SRCS src *.c)

add_executable(server ${_SRCS})
target_link_libraries(server ${MYSQL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} comm rftg)

