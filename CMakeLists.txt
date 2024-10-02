cmake_minimum_required(VERSION 3.1)

project(MotorControlProject 
    LANGUAGES CXX)

add_executable(motor_test)

target_sources(motor_test PRIVATE src/main.cpp src/motor_controller.cpp src/motor_controller.hpp)

find_library(PIGPIOD_IF_LIB pigpiod_if2)
find_library(PIGPIO_LIB pigpio)

target_link_libraries(motor_test ${PIGPIO_LIB} ${PIGPIOD_IF_LIB})