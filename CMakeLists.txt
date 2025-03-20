cmake_minimum_required(VERSION 3.28.3)

project(GBemu C)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BUILD_TYPE Debug)

###############################################################################
# Modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Subdirectories
add_subdirectory(lib)
add_subdirectory(GBemu)