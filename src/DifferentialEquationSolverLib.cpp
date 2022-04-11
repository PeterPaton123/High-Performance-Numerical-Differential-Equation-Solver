#include "DifferentialEquationSolver.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(HP_Numerical_DE_Solver, m) {
    py::class_<DifferentialEquationSolver>(m, "DifferentialEquationSolver")
        .def(py::init<std::function<float(float, float)>&, const float&, const float&, const float&, const float&>())
        .def("perform_picard_iterations", &DifferentialEquationSolver::perform_picard_iterations)
        .def("get_function_points", &DifferentialEquationSolver::get_function_points)
        .def("get_sample_times_before_t0", &DifferentialEquationSolver::get_sample_times_before_t0)
        .def("get_sample_times_after_t0", &DifferentialEquationSolver::get_sample_times_after_t0);
}