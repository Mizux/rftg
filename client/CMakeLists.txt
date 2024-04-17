find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED IMPORTED_TARGET gtk+-2.0)
#pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.c")

add_library(client ${_HDRS} ${_SRCS})
target_include_directories(client PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")
target_link_libraries(client PRIVATE
  ${GTK2_LIBRARIES}
  RFTG::rftg
  RFTG::comm
  PkgConfig::GTK2)
  #PkgConfig::GTK4)
add_library(RFTG::client ALIAS client)

install(
  TARGETS client
	EXPORT RFTGTargets
  DESTINATION lib
  COMPONENT RUNTIME)
