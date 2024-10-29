# CMakeLists.txt for the server

cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 11)

# Add the server executable
add_executable(server src/server.cpp)

# Link libraries (for Linux, none needed, but for clarity's sake we include socket libraries)
target_link_libraries(server PRIVATE pthread)
