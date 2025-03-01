cmake_minimum_required (VERSION 2.8.8 FATAL_ERROR)

project (VL53L0X_linux)

### Setup compiler
# Set warning flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2 -Wall -Wextra")
# Set optimalization flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
# Set C++ standard
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

### Examples
add_subdirectory (examples)
