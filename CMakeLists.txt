cmake_minimum_required(VERSION 3.20)

project(SmartStick)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

# Find the libgpiod package
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGPIO REQUIRED libgpiod)

set(FASTDDS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/fastdds")
set(TOPICS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/topics")
set(DRIVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}src/drivers/)

# Include custom functions
include("functions.cmake")

include_directories(${TOPICS_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/fastdds)
create_msg_library(HelloWorldMsg)

# Add include directories for gpiod and include folder
include_directories(${LIBGPIO_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/drivers/)
include_directories(${DRIVER_DIR}/vl53l0x-linux/)


# Add executable for publisher
set (PUB_SOURCES
     src/main_pub.cpp
    )

set (SUB_SOURCES
     src/main_sub.cpp
    )
add_executable(DDSPublisher ${PUB_SOURCES})
target_link_libraries(DDSPublisher fastcdr fastrtps HelloWorldMsg)

add_executable(DDSSubscriber ${SUB_SOURCES})
target_link_libraries(DDSSubscriber fastcdr fastrtps HelloWorldMsg)

# set(SOURCES
#     main.cpp
#     ${DRIVER_DIR}/sensors/sensors.cpp
#     ${DRIVER_DIR}/sensors/tof_sensor.cpp)    

# set(TOF_SOURCES
#     ${DRIVER_DIR}/vl53l0x-linux/VL53L0X.cpp
#     ${DRIVER_DIR}/vl53l0x-linux/I2Cdev.cpp
#     )

# add_executable(SensorApp ${SOURCES} ${TOF_SOURCES})
# target_link_libraries(SensorApp ${LIBGPIO_LIBRARIES})
