# Create App Manager Library
add_library(app_manager src/manager.cpp)

# Include App Manager Headers
target_include_directories(app_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)