cmake_minimum_required(VERSION 3.20)

# SWIG: use standard target name.
if(POLICY CMP0078)
  cmake_policy(SET CMP0078 NEW)
endif()


# SWIG: use SWIG_MODULE_NAME property.
if(POLICY CMP0086)
  cmake_policy(SET CMP0086 NEW)
endif()

project(SmartStick)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

find_package(fastcdr REQUIRED)
find_package(fastdds REQUIRED)

find_package(SWIG)
if (NOT SWIG_FOUND)
    # Trick to find swig4.1 in Ubuntu noble.
    find_program(SWIG_EXECUTABLE NAMES swig4.1 swig)
    find_package(SWIG REQUIRED)
endif()
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
set(PYTHON_INCLUDE_PATH ${Python3_INCLUDE_DIRS})
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})
set(PYTHON_LIBRARIES ${Python3_LIBRARIES})
include_directories(${PYTHON_INCLUDE_PATH})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS ON)


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

set(MAIN_SOURCES
    src/main.cpp
    ${APPLICATION_DIR}/MotorMove.cpp
    ${APPLICATION_DIR}/DDSCommunicator.cpp
    ${TOF_SOURCES}
)

add_executable(SmartWalkingStick ${MAIN_SOURCES})

target_link_libraries(SmartWalkingStick ${LIBGPIO_LIBRARIES} gpiod fastcdr fastdds ToFData MotorCommands)


