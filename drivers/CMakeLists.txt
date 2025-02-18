cmake_minimum_required(VERSION 3.10)

project(drivers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the libgpiod package
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGPIO REQUIRED libgpiod)

# Add include directories for gpiod and include folder
include_directories(${LIBGPIO_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vl53l0x-linux/)

set(SOURCES
    src/main.cpp
    src/sensors.cpp
    src/tof_sensor.cpp)    

set(TOF_SOURCES
    vl53l0x-linux/VL53L0X.cpp
    vl53l0x-linux/I2Cdev.cpp
    )

add_executable(SensorApp ${SOURCES} ${TOF_SOURCES})
target_link_libraries(SensorApp ${LIBGPIO_LIBRARIES})
