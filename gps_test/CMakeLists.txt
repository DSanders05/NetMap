cmake_minimum_required(VERSION 3.10)

# Project name
project(GPSReader)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to MAVLink headers (adjust this path to the actual location where you generated the MAVLink headers)
include_directories(${PROJECT_SOURCE_DIR}/mavlink/generated/include/common/mavlink.h)

# Add executable target
add_executable(gps_reader src/gps_reader.cpp)
add_executable(byte_reader src/byte_reader.cpp)

# Link necessary libraries for serial port communication (if required)
# Add any additional libraries if you need them (e.g., pthread for threading, etc.)
target_link_libraries(gps_reader PRIVATE pthread)

# For verbose output
#set(CMAKE_VERBOSE_MAKEFILE ON)
