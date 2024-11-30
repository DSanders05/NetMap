cmake_minimum_required(VERSION 3.10)

# Project name
project(NetMap)

# C++ Standard
set(CMAKE__CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(app_manager)
add_subdirectory(communications/client)
# add_subdirectory(communications/server)
add_subdirectory(motor_controls)

add_executable(net_map main.cpp)

target_link_libraries(net_map PRIVATE app_manager client motor_controller)