cmake_minimum_required(VERSION 3.10)

# Project name
project(NetMap)

# C++ Standard
set(CMAKE__CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Python3_INCLUDE_DIRS /usr/include/python3.10)

# Find Python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Subdirectories
add_subdirectory(app_manager)
add_subdirectory(communications/client)
add_subdirectory(communications/server)
add_subdirectory(motor_controls)

# Add PyBind11 Submodule
# add_subdirectory(external/pybind11)

# Main Executable
add_executable(net_map ./main.cpp)

target_include_directories(net_map PRIVATE ${Python3_INCLUDE_DIRS})

# Link Libraries
# target_link_libraries(net_map PRIVATE app_manager client motor_controller pybind11::module Python3::Python)
target_link_libraries(net_map PRIVATE app_manager client motor_controller pthread)