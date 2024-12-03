#include <pybind11/pybind11.h>
#include "../include/manager.hpp"

namespace py = pybind11;

PYBIND11_MODULE(manager_bindings, m)
{
    py::class_<Manager>(m, "Manager")
        // Binding for the constructor
        .def(py::init([]() {
            std::vector<std::string> server_ips = {"192.168.2.22"
                                                                        ,"192.168.2.33"
                                                                        ,"192.168.2.44"
                                                                        ,"192.168.2.55"};
            int server_port = 8080;
            return new Manager(server_ips, server_port);
        }))
        // Binding for the start scan function
        .def("start_auto_mode", &Manager::start_auto_mode, "Starts auto scanning mode.");
}