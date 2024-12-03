cmake_minimum_required(VERSION 3.10)

# Project name
project(NetMap)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Python3_INCLUDE_DIRS /usr/include/python3.10)

# Add PyBind11 Submodule
add_subdirectory(external/pybind11)


# Find Python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/external/pybind11")

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
# find_package(pybind11 CONFIG)


# Subdirectories
add_subdirectory(app_manager)
add_subdirectory(communications/client)
add_subdirectory(communications/server)
add_subdirectory(motor_controls)

# Main Executable
add_executable(net_map ./main.cpp)

target_include_directories(net_map PRIVATE ${Python3_INCLUDE_DIRS})

# Link Libraries
target_link_libraries(net_map PRIVATE app_manager client motor_controller pybind11::module Python3::Python pthread)
# target_link_libraries(net_map PRIVATE app_manager client motor_controller pthread)