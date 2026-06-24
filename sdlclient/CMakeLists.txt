find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(SDL3_IMAGE REQUIRED sdl3-image)

file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.c")

add_executable(sdlclient ${_HDRS} ${_SRCS})
target_include_directories(sdlclient PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${SDL3_INCLUDE_DIRS}"
  "${SDL3_IMAGE_INCLUDE_DIRS}")

target_link_libraries(sdlclient PRIVATE
  ${SDL3_LIBRARIES}
  ${SDL3_IMAGE_LIBRARIES}
  RFTG::rftg
  RFTG::comm)
