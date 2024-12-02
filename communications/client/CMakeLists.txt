# Create Client Library
add_library(client src/Client.cpp)

# Include Client Library Headers
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)