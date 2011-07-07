cmake_minimum_required(VERSION 2.8)

project(enginetest)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

include_directories("${PROJECT_SOURCE_DIR}/cxxtest")

add_subdirectory (src) 

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
set(DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)

set(GEN_DISCLAIMER
   "// This file was generated using cmake, any modifications will be overwritten")

configure_file(
  "${PROJECT_SOURCE_DIR}/src/cconfig.h.in"
  "${PROJECT_SOURCE_DIR}/src/cconfig.h")