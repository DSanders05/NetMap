#include <iostream>
#include "./motor_controller.hpp"
#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char* argv[])
{
    std::cout << "Starting Python Gui." << std::endl;
    // Motor_Controller controller = Motor_Controller();
    // controller.claim_pins();
    // controller.initialize_heading();
    // controller.get_heading();
    // controller.scan_area();

    py::scoped_interpreter guard{};
    py::module netmap_gui = py::module::import("App");
    netmap_gui.attr("startApp")();
    
    std::cout << "Python GUI Test Complete." << std::endl;

    return 0;
}