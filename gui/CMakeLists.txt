find_package(GTK2 REQUIRED)
include_directories(${GTK2_INCLUDE_DIRS})

file(GLOB_RECURSE _SRCS "src/*.c")

add_executable(gui ${_SRCS})
target_link_libraries(gui PRIVATE ${GTK2_LIBRARIES} RFTG::rftg RFTG::client RFTG::comm)
