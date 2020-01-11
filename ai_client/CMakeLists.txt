file(GLOB_RECURSE _SRCS "src/*.c")

add_executable(ai_client ${_SRCS})
target_link_libraries(ai_client PRIVATE RFTG::rftg RFTG::comm RFTG::net)

