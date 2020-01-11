file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.c")

add_library(comm ${_HDRS} ${_SRCS})
target_include_directories(comm PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
target_link_libraries(comm PRIVATE RFTG::rftg)
add_library(RFTG::comm ALIAS comm)

install(
  TARGETS comm
	EXPORT RFTGTargets
  DESTINATION lib
  COMPONENT RUNTIME)
