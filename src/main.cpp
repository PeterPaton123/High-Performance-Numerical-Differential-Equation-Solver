#include <iostream>
#include "DifferentialEquationSolver.hpp"

float ex(float x, float t) {
    return x;
}

int main() {
    std::function<float(float,float)> eg = ex;
    DifferentialEquationSolver eq = DifferentialEquationSolver(eg, 0, 1, -10, 10);
    eq.perform_picard_iterations(100);
    std::cout << "[";
    for (int i = 0; i <= 99; i++) {
        std::cout << "(" << eq.get_sample_times_before_t0()[i] << ", " << eq.get_function_points()[i] << "), ";
    }
    for (int i = 100; i < 201; i++) {
        std::cout << "(" << eq.get_sample_times_after_t0()[i-100] << ", " << eq.get_function_points()[i] << "), ";
    }
    std::cout << "]";
    return 0;
}
 