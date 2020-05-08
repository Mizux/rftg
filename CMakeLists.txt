cmake_minimum_required(VERSION 3.14)
project(RFTGGame VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Include file check macros honor CMAKE_REQUIRED_LIBRARIES.
if(POLICY CMP0075)
  cmake_policy(SET CMP0075 NEW)
endif()

# Force default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
    "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
    FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
if(UNIX)
  option(BUILD_SHARED_LIBS "Build shared libraries(.so or .dylib)." ON)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  if(APPLE)
    set(CMAKE_INSTALL_RPATH "@loader_path;@loader_path/../${CMAKE_INSTALL_LIBDIR}")
  else()
    set(CMAKE_INSTALL_RPATH "$ORIGIN:$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
  endif()
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  set(CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_DOCDIR})
else()
  # only support for static build on Windows.
  set(BUILD_SHARED_LIBS OFF)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${CMAKE_INSTALL_BINDIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${CMAKE_INSTALL_BINDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${CMAKE_INSTALL_BINDIR})
  set(CMAKE_DOCUMENTATION_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${CMAKE_INSTALL_DOCDIR})
endif()

include(CTest)
include(FetchContent)
if(BUILD_TESTING)
  #FetchContent_Declare(
  #  googletest
  #  GIT_REPOSITORY https://github.com/google/googletest.git
  #  GIT_TAG release-1.10.0)
  #set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  #FetchContent_MakeAvailable(googletest)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG master
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    )
  FetchContent_MakeAvailable(Catch2)
endif()

# LIBRARIES
add_subdirectory(net)
add_subdirectory(rftg)
add_subdirectory(comm)
add_subdirectory(client)

# EXECUTABLES
add_subdirectory(gui)
add_subdirectory(server)
add_subdirectory(ai_client)
add_subdirectory(learner)
add_subdirectory(dumpnet)

# Install
install(
  EXPORT RFTGTargets
  NAMESPACE RFTG::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RFTG
  COMPONENT Devel)
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/RFTGConfig.cmake.in
  "${PROJECT_BINARY_DIR}/RFTGConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/RFTG"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/RFTGConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion)
install(
  FILES
  "${PROJECT_BINARY_DIR}/RFTGConfig.cmake"
  "${PROJECT_BINARY_DIR}/RFTGConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/RFTG"
  COMPONENT Devel)
