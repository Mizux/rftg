file(GLOB_RECURSE _SRCS "src/*.c")

add_executable(dumpnet ${_SRCS})
target_link_libraries(dumpnet RFTG::net)

