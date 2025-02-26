cmake_minimum_required(VERSION 3.20)

project(SmartStick)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

set(FASTDDS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/fastdds")
set(TOPICS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/topics")

# Include custom functions
include("functions.cmake")

include_directories(${TOPICS_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/fastdds)
create_msg_library(ToFData)

# Add executable for publisher
set (PUB_SOURCES
     ${FASTDDS_DIR}/ToFDataPublisher.cpp
     src/main.cpp
    )

add_executable(DDSPublisher ${PUB_SOURCES})
target_link_libraries(DDSPublisher fastcdr fastrtps ToFData)

