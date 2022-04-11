import HP_Numerical_DE_Solver as HPNDES
import numpy as np
import matplotlib.pyplot as plt
import math
import sys

def printf(format, *args):
    sys.stdout.write(format % args)

class Solver:
    def derivative(__self__, x, t):
        return x

    def solution(__self__, t):
        return math.exp(t)
    
def example(x, t):
    return math.cos(math.sin(x*t)*t)

solver = Solver()
de = HPNDES.DifferentialEquationSolver(solver.derivative, 0.0, 1.0, -10.0, 10.0)
solution = np.array([solver.solution(xi) for xi in np.concatenate((de.get_sample_times_before_t0(), de.get_sample_times_after_t0()[1:]))])

colours = ['b', 'g', 'r', 'c', 'm', 'y']

for i in range(0, 6):
    function_points = np.array(de.get_function_points())
    sample_points_before_t0 = np.array(de.get_sample_times_before_t0())
    sample_points_after_t0 = np.array(de.get_sample_times_after_t0())
    #print(np.size(sample_points_after_t0[0:]))
    plt.plot(sample_points_before_t0, function_points[:101], ls='--', color = colours[i], alpha=1.0)
    plt.plot(sample_points_after_t0[0:], function_points[100:], ls='--', color = colours[i], alpha=1.0)
    de.perform_picard_iterations(4)
    printf("Picard iteration %d: RMSE=%f\n", 4*i, np.sqrt(np.mean((function_points-solution)**2)))

plt.plot(np.array(de.get_sample_times_before_t0()), np.array([solver.solution(xi) for xi in np.array(de.get_sample_times_before_t0())]), ls='-', color='k', alpha=0.5)
plt.plot(np.array(de.get_sample_times_after_t0()), np.array([solver.solution(xi) for xi in np.array(de.get_sample_times_after_t0())]), ls='-', color='k', alpha=0.5)

plt.show()