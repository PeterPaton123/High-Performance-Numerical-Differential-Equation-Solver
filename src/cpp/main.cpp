#include <iostream>
#include "de.hpp"

float ex(float x, float t) {
    return x;
}

int main() {
    std::function<float(float,float)> eg = ex;
    de eq = de(eg, 0, 1, -10, 10);
    for (int i = 0; i < 100; i++) {
        eq.picard_iteration();
    }
    std::cout << "[";
    for (int i = 0; i <= 99; i++) {
        std::cout << "(" << eq.sample_times_before_t0[i] << ", " << eq.picard_iteration_x_at_time_t[i] << "), ";
    }
    for (int i = 100; i < 201; i++) {
        std::cout << "(" << eq.sample_times_after_t0[i-100] << ", " << eq.picard_iteration_x_at_time_t[i] << "), ";
    }
    std::cout << "]";
    return 0;
}
 