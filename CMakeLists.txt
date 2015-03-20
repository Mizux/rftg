cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# LIBRARIES
add_subdirectory(rftg)
add_subdirectory(comm)
add_subdirectory(net)
add_subdirectory(client)

# EXECUTABLES
add_subdirectory(gui)
add_subdirectory(server)
add_subdirectory(ai_client)
add_subdirectory(learner)
add_subdirectory(dumpnet)
