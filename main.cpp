#include <pybind11/pybind11.h>
#include "app_manager/include/manager.hpp"

namespace py = pybind11;

int main(int argc, char* argv[])
{
    try
    {
        // Initialize python interpreter
        Py_Initialize();

        // Acquire global interp lock
        py::gil_scoped_acquire acquire;

        // Add path to python module
        py::module_ sys = py::module_::import("sys");
        sys.attr("path").attr("append")("../user_interface");

        // Import and run GUI interface
        py::module_ interface = py::module_::import("interface");
        interface.attr("start_ui")();
    }
    catch(const py::error_already_set& e)
    {
        std::cerr << "Python interface error: " << e.what() << std::endl;
    }
        
    // Close python interpreter
    Py_Finalize();
    
    return 0;
}