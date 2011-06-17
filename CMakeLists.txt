cmake_minimum_required (VERSION 2.6)

project(enginetest)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)

include_directories ("${PROJECT_SOURCE_DIR}/cxxtest")

add_subdirectory (src) 
