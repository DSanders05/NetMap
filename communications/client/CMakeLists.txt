# Create Client Library
add_library(client STATIC src/Client.cpp)

set_target_properties(client PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Include Client Library Headers
target_include_directories(client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)