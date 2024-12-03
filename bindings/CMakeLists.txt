find_package(pybind11 REQUIRED)

# Create python bindings
pybind11_add_module(manager_bindings src/bindings.cpp)

# Include manager class directories
target_include_directories(manager_bindings PRIVATE
    ${CMAKE_SOURCE_DIR}/app_manager/include
    ${CMAKE_SOURCE_DIR}/communications/client/include
    ${CMAKE_SOURCE_DIR}/motor_controls/include
)

target_link_libraries(manager_bindings PRIVATE app_manager motor_controller client)

set_target_properties(manager_bindings PROPERTIES PREFIX "")
set_target_properties(manager_bindings PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})