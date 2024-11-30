# Create Motor Controller Library
add_library(motor_controller src/motor_controller.cpp)

# Include Motor Controller Headers
target_include_directories(motor_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link PIGPIO Library
target_link_libraries(motor_controller PRIVATE pigpiod_if2)