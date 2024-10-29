cmake_minimum_required(VERSION 3.1)

project(
    LimitTestProject
    LANGUAGES CXX
)

add_executable(sw_test)

target_sources(sw_test PRIVATE src/main.cpp)

find_library(PIGPIOD_IF_LIB pigpiod_if2)
find_library(PIGPIO_LIB pigpio)

target_link_libraries(sw_test ${PIGPIO_LIB} ${PIGPIOD_IF_LIB})