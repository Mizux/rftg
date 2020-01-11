file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.c")

add_library(net ${_HDRS} ${_SRCS})
target_include_directories(net PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
target_link_libraries(net PRIVATE m)
add_library(RFTG::net ALIAS net)

install(
  TARGETS net
	EXPORT RFTGTargets
  DESTINATION lib
  COMPONENT RUNTIME)
