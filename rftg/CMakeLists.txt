file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.c")

add_library(rftg ${_HDRS} ${_SRCS})
target_include_directories(rftg PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
target_link_libraries(rftg RFTG::net)
add_library(RFTG::rftg ALIAS rftg)

install(
  TARGETS rftg
	EXPORT RFTGTargets
  DESTINATION lib
  COMPONENT RUNTIME)
