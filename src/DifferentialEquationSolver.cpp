#include "DifferentialEquationSolver.hpp"
#include <iostream>

DifferentialEquationSolver::DifferentialEquationSolver(std::function<float(float, float)> derivative_in, float t0, float x0, float t_max_minus, float t_max_plus) : t0(t0), x0(x0) {
    derivative = std::make_shared<std::function<float(float, float)>>(derivative_in);
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

DifferentialEquationSolver::~DifferentialEquationSolver() {}

void DifferentialEquationSolver::perform_picard_iterations(int iterations) {
    for (int i = 0; i < iterations; i++) {
        picard_iteration();
    }
}

inline void DifferentialEquationSolver::picard_iteration() {
    // perform a single picard iteration
    std::array<float, 201> new_picard_iteration_x_at_time_t;
    new_picard_iteration_x_at_time_t[100] = x0;
    for(int i = 1; i <= 100; i++) {
        float integral_ti_negative_direction = 0.5 * 
            ((*derivative)(picard_iteration_x_at_time_t[100-i], sample_times_before_t0[100-i]) + (*derivative)(picard_iteration_x_at_time_t[100-(i-1)], sample_times_before_t0[100-(i-1)]))
                * (sample_times_before_t0[100-i] - sample_times_before_t0[100-(i-1)]);
        float integral_ti_positive_direction = 0.5 * 
            ((*derivative)(picard_iteration_x_at_time_t[100+i], sample_times_after_t0[i]) + (*derivative)(picard_iteration_x_at_time_t[100+(i-1)], sample_times_after_t0[i-1]))
                * (sample_times_after_t0[i] - sample_times_after_t0[i-1]);
        new_picard_iteration_x_at_time_t[100-i] = new_picard_iteration_x_at_time_t[100-(i-1)] + integral_ti_negative_direction;
        new_picard_iteration_x_at_time_t[100+i] = new_picard_iteration_x_at_time_t[100+(i-1)] + integral_ti_positive_direction;
    
    }
    picard_iteration_x_at_time_t = new_picard_iteration_x_at_time_t;
}

std::array<float, 201> DifferentialEquationSolver::get_function_points() const {
    return picard_iteration_x_at_time_t;
}

std::array<float, 101> DifferentialEquationSolver::get_sample_times_before_t0() const {
    return sample_times_before_t0;
}

std::array<float, 101> DifferentialEquationSolver::get_sample_times_after_t0() const {
    return sample_times_after_t0;
}