#include <array>
#include <memory>
#include <functional>

class de {   
public:
    de(std::function<float(float, float)> derivative, float t0, float x0, float t_max_minus, float t_max_plus);
    ~de();
    void picard_iteration();
    std::array<float, 201> get_function_points() const;
    std::array<float, 101> get_sample_times_before_t0() const;
    std::array<float, 101> get_sample_times_after_t0() const;
//private:
    const std::function<float(float, float)> derivative; // dx/dt
    const float x0;
    const float t0;
    const int samples = 100;
    // change to samples
    std::array<float, 201> picard_iteration_x_at_time_t;
    // Both these arrays include t0
    std::array<float, 101> sample_times_before_t0;
    std::array<float, 101> sample_times_after_t0;
};
