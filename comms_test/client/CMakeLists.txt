# CMakeLists.txt for the client

cmake_minimum_required(VERSION 3.10)
project(Client)

set(CMAKE_CXX_STANDARD 11)

# Add the client executable
add_executable(client src/client.cpp)

# Link libraries (for Linux, none needed, but for clarity's sake we include socket libraries)
target_link_libraries(client PRIVATE pthread)
