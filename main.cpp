#include <pybind11/pybind11.h>
#include "app_manager/include/manager.hpp"

namespace py = pybind11;

int main(int argc, char* argv[])
{
    try
    {
        //Init python interpreter
        Py_Initialize();

        // Acquire global interp lock
        py::gil_scoped_acquire acquire;

        // Add path to python module
        py::module_ sys = py::module_::import("sys");
        sys.attr("path").attr("append")("../user_interface");

        // Import and run interface
        py::module_ interface = py::module_::import("interface");
        interface.attr("start_ui")();
    }
    catch(const py::error_already_set& e)
    {
        std::cerr << "Python interface error: " << e.what() << std::endl;
    }
        
    // Finalize interpreter
    Py_Finalize();

    std::vector<std::string> rover_ips = {
        "192.168.2.22",
        "192.168.2.33",
        "192.168.2.44",
        "192.168.2.55"
    };

    // Manager net_map = Manager(rover_ips, 8080);

    // net_map.start_auto_mode();
    
    return 0;
}