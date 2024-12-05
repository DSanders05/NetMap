#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "manager.hpp"

namespace py = pybind11;

PYBIND11_MODULE(manager_bindings, m) {
    m.doc() = "Python bindings for Manager class";

    py::class_<Manager>(m, "Manager")
        .def(py::init<const std::vector<std::string>&, int>(), py::arg("server_ips"), py::arg("server_port"))
        .def("start_auto_mode", &Manager::start_auto_mode)
        .def("setup_zero", &Manager::setup_zero)
        .def("update_rovers", &Manager::update_rovers)
        .def("turn_to_target", &Manager::turn_to_target)
        .def("turn_to_zero", &Manager::turn_to_target)
        .def("get_rovers",&Manager::get_rovers);
}
