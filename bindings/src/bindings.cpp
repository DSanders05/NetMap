#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "manager.hpp"

namespace py = pybind11;

// Creates a python module to import in order
// to give access to C++ Manager class functions
PYBIND11_MODULE(manager_bindings, m) {
    m.doc() = "Python bindings for Manager class";

    // Defines the class Manager to python
    // with each ".def" method exposing these functions to python
    py::class_<Manager>(m, "Manager")
        .def(py::init<std::vector<std::string>&, int>(), py::arg("server_ips"), py::arg("server_port"))
        .def("start_thread",&Manager::start_thread)
        .def("start_auto_mode",&Manager::start_auto_mode)
        .def("init_zero",&Manager::init_zero)
        .def("update_rovers",&Manager::update_rovers)
        .def("turn_to_target",&Manager::turn_to_target)
        .def("turn_to_zero",&Manager::turn_to_target)
        .def("stop_auto_mode",&Manager::stop_auto_mode);
}
