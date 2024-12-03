# Create App Manager Library
add_library(app_manager STATIC src/manager.cpp)

set_target_properties(app_manager PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Include App Manager Headers
target_include_directories(app_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)