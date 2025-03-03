cmake_minimum_required(VERSION 3.10)

project(drivers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(DRIVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/)

# Find the libgpiod package
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGPIO REQUIRED libgpiod)


# Add include directories for gpiod and include folder
include_directories(${LIBGPIO_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/drivers/)
include_directories(${DRIVER_DIR}/vl53l0x-linux/)


set(SOURCES
    src/main.cpp
    ${DRIVER_DIR}/sensors/sensors.cpp
    ${DRIVER_DIR}/sensors/tof_sensor.cpp)    

set(TOF_SOURCES
    ${DRIVER_DIR}/vl53l0x-linux/VL53L0X.cpp
    ${DRIVER_DIR}/vl53l0x-linux/I2Cdev.cpp
    )

add_executable(SensorApp ${SOURCES} ${TOF_SOURCES})
target_link_libraries(SensorApp ${LIBGPIO_LIBRARIES})
