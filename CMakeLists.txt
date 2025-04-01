cmake_minimum_required(VERSION 3.20)

project(SmartStick)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


# Find the libgpiod package
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGPIO REQUIRED libgpiod)

set(FASTDDS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/fastdds")
set(TOPICS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/topics")
set(DRIVER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/")
set(APPLICATION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/application")

# Include custom functions
include("functions.cmake")
include(GNUInstallDirs)

add_compile_options(-Wall -Wconversion -Wextra -pedantic)

include_directories(${TOPICS_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/fastdds)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/application)
create_msg_library(ToFData)
create_msg_library(MotorCommands)

# Add include directories for gpiod and include folder
include_directories(${LIBGPIO_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/drivers/)
include_directories(${DRIVER_DIR}/vl53l0x-linux/)

set(TOF_SOURCES
    ${DRIVER_DIR}/vl53l0x-linux/VL53L0X.cpp
    ${DRIVER_DIR}/vl53l0x-linux/I2Cdev.cpp
    ${DRIVER_DIR}/sensors/tof_sensor.cpp
    )

# # Add executable for publisher
# set(SOURCES
#     src/main_combined.cpp
#     ${TOF_SOURCES}
#     ${APPLICATION_DIR}/ToFDataPublisher.cpp
#     ${APPLICATION_DIR}/MotorMove.cpp
#     )

set(TEST_SOURCES
    src/tester_main.cpp
    ${APPLICATION_DIR}/MotorMove.cpp
    ${TOF_SOURCES}
)

add_executable(TofTest ${TEST_SOURCES})

target_link_libraries(TofTest ${LIBGPIO_LIBRARIES} gpiod)


# message(STATUS "SUB_SOURCES: ${SUB_SOURCES}")
# add_executable(DDSPublisher ${PUB_SOURCES})
# target_link_libraries(DDSPublisher fastcdr fastrtps ToFData MotorCommands)

# add_executable(DDSSubscriber ${SUB_SOURCES})
# target_link_libraries(DDSSubscriber fastcdr fastrtps ToFData MotorCommands)
#

# add_executable(CombinedSystem ${SOURCES})
# target_link_libraries(CombinedSystem fastcdr fastrtps ToFData MotorCommands ${LIBGPIO_LIBRARIES})

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
