# Create Motor Controller Library
add_library(motor_controller STATIC src/motor_controller.cpp)

set_target_properties(motor_controller PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Include Motor Controller Headers
target_include_directories(motor_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link PIGPIO Library
target_link_libraries(motor_controller PRIVATE pigpiod_if2)