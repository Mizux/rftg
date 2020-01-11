file(GLOB_RECURSE _SRCS "src/*.c")

add_executable(learner ${_SRCS})
target_link_libraries(learner RFTG::rftg)

