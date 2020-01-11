# Find MySQL
find_package(MySQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIRS})
# Find pthread
find_package(Threads REQUIRED)

file(GLOB_RECURSE _SRCS "src/*.c")

add_executable(server ${_SRCS})
target_link_libraries(server
	${MYSQL_LIBRARIES}
	Threads::Threads
	RFTG::comm
	RFTG::rftg)
