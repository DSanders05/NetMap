cmake_minimum_required(VERSION 3.1)

project(netmap_app 
    LANGUAGES CXX)

add_subdirectory(extern/pybind11)

add_executable(netmap_app)

target_sources(netmap_app PRIVATE src/main.cpp src/motor_controller.cpp src/motor_controller.hpp)

find_library(PIGPIOD_IF_LIB pigpiod_if2)
find_library(PIGPIO_LIB pigpio)

target_link_libraries(netmap_app ${PIGPIO_LIB} ${PIGPIOD_IF_LIB} pybind11::embed)
#target_include_directories(NetMap PRIVATE ${CMAKE_SOURCE_DIR}/src)
