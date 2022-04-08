#include "de.hpp"
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

de::de(std::function<float(float, float)> derivative, float t0, float x0, float t_max_minus, float t_max_plus) : derivative(derivative), t0(t0), x0(x0) {
    // set up initial picard iteration f0(t) = x0
    for(int i = 0; i < 201; i++) {
        picard_iteration_x_at_time_t[i] = x0;
    }
    for(int i = 0; i < 100; i++) {
        sample_times_before_t0[i] = t_max_minus + ((t0 - t_max_minus) * i / 101);
        sample_times_after_t0[i+1] = t0 + ((t_max_plus - t0) * (i + 1) / 101);
    }
    sample_times_before_t0[100] = t0;
    sample_times_after_t0[0] = t0;
}

de::~de() {}

void de::picard_iteration() {
    // perform a single picard iteration
    std::array<float, 201> new_picard_iteration_x_at_time_t;
    new_picard_iteration_x_at_time_t[100] = x0;
    for(int i = 1; i <= 100; i++) {
        /*
        The value of the picard itertion function n at a time sample i away from t0
        is the value at i - 1 plus the additional intergral from ti-1 to ti 
        */
        float integral_ti_negative_direction = 0.5 * 
            (derivative(picard_iteration_x_at_time_t[100-i], sample_times_before_t0[100-i]) + derivative(picard_iteration_x_at_time_t[100-(i-1)], sample_times_before_t0[100-(i-1)]))
                * (sample_times_before_t0[100-i] - sample_times_before_t0[100-(i-1)]);

        //std::cout << (sample_times_after_t0[100-i] - sample_times_after_t0[100-(i-1)]) << std::flush;
        
        float integral_ti_positive_direction = 0.5 * 
            (derivative(picard_iteration_x_at_time_t[100+i], sample_times_after_t0[i]) + derivative(picard_iteration_x_at_time_t[100+(i-1)], sample_times_after_t0[i-1]))
                * (sample_times_after_t0[i] - sample_times_after_t0[i-1]);

        //std::cout << derivative(picard_iteration_x_at_time_t[100+i], sample_times_after_t0[i]) << std::flush;
        new_picard_iteration_x_at_time_t[100-i] = new_picard_iteration_x_at_time_t[100-(i-1)] + integral_ti_negative_direction;
        new_picard_iteration_x_at_time_t[100+i] = new_picard_iteration_x_at_time_t[100+(i-1)] + integral_ti_positive_direction;
    }
    picard_iteration_x_at_time_t = new_picard_iteration_x_at_time_t;
}

std::array<float, 201> de::get_function_points() const {
    return picard_iteration_x_at_time_t;
}

std::array<float, 101> de::get_sample_times_before_t0() const {
    return sample_times_before_t0;
}

std::array<float, 101> de::get_sample_times_after_t0() const {
    return sample_times_after_t0;
}

PYBIND11_MODULE(ball, m) {
    py::class_<Ball>(m, "Ball")
        .def(py::init<const double&, const double&>())
        .def("timestep1000", &Ball::timestep1000)
        .def("gety0", &Ball::gety0);
}