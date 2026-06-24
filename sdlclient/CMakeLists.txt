
# SDL
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
#find_package(SDL3_ttf REQUIRED)
#find_package(SDL3_mixer REQUIRED)

file(GLOB_RECURSE _HDRS "include/*.h")
file(GLOB_RECURSE _SRCS "src/*.c")

add_executable(sdlclient ${_HDRS} ${_SRCS})
target_include_directories(sdlclient PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(sdlclient PRIVATE
  "SDL3::SDL3"
  "SDL3_image::SDL3_image"
  RFTG::rftg
  RFTG::comm)
