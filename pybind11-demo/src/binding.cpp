#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "math_utils.h"

namespace py = pybind11;

PYBIND11_MODULE(pymylib, m) {
    m.doc() = "Python binding for mylib - a utilities modern C++ math library";
    
    // Version
    m.attr("__version__") = "1.0.0";
    
    // Result struct
    py::class_<mylib::Result>(m, "Result")
        .def(py::init<double, std::string>())
        .def_readonly("value", &mylib::Result::value)
        .def_readonly("description", &mylib::Result::description)
        .def("__repr__", [](const mylib::Result& r) {
            return "<pymylib.Result value=" + std::to_string(r.value) + 
                   " description='" + r.description + "'>";
        });
    
    // Calculator class
    py::class_<mylib::Calculator>(m, "Calculator")
        .def(py::init<>())
        .def("add", &mylib::Calculator::add, "Add two numbers")
        .def("subtract", &mylib::Calculator::subtract, "Subtract two numbers")
        .def("multiply", &mylib::Calculator::multiply, "Multiply two numbers")
        .def("divide", &mylib::Calculator::divide, "Divide two numbers")
        .def("compute_stats", &mylib::Calculator::compute_stats, 
             py::arg("data"),
             "Compute statistics for a dataset")
        .def_static("version", &mylib::Calculator::version, "Get version string");
}
