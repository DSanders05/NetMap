# Create App Manager Library
add_library(app_manager src/manager.cpp)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/external/pybind11")
# Find PyBind11 (goodluck)
# find_package(pybind11 CONFIG)

# Build Python Bindings
pybind11_add_module(manager_bindings src/bindings.cpp src/manager.cpp)

# Output directory for manager_bindings module
set_target_properties(manager_bindings PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python_bindings)

# Include App Manager Headers
target_include_directories(app_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)