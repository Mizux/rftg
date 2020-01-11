find_package(GTK2 REQUIRED)
include_directories(${GTK2_INCLUDE_DIRS})

file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.c")

add_library(client ${_HDRS} ${_SRCS})
target_include_directories(client PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
target_link_libraries(client PRIVATE ${GTK2_LIBRARIES} RFTG::rftg RFTG::comm)
add_library(RFTG::client ALIAS client)

install(
  TARGETS client
	EXPORT RFTGTargets
  DESTINATION lib
  COMPONENT RUNTIME)
