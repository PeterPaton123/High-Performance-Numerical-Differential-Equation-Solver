import HP_Numerical_DE_Solver as HPNDES
import numpy as np
import matplotlib.pyplot as plt
import math
import sys

def printf(format, *args):
    sys.stdout.write(format % args)
    
# DE which solves to exp(t) (The math.exp function in python)
def example_de(x, t): 
    return x

de = HPNDES.DifferentialEquationSolver(example_de, 0.0, 1.0, -10.0, 10.0)
solution_points = np.array([math.exp(xi) for xi in np.concatenate((de.get_sample_times_before_t0(), de.get_sample_times_after_t0()[1:]))])

colours = ['y', 'g', 'b', 'c', 'm', 'r']

for i in range(0, 6):
    function_points = np.array(de.get_function_points())
    sample_points_before_t0 = np.array(de.get_sample_times_before_t0())
    sample_points_after_t0 = np.array(de.get_sample_times_after_t0())
    #print(np.size(sample_points_after_t0[0:]))
    plt.plot(sample_points_before_t0, function_points[:101], ls='--', color = colours[i], alpha=1.0)
    plt.plot(sample_points_after_t0[0:], function_points[100:], ls='--', color = colours[i], alpha=1.0)
    de.perform_picard_iterations(4)
    printf("Picard iteration %d: RMSE=%f\n", 4*i, np.sqrt(np.mean((function_points-solution_points)**2)))

plt.plot(np.array(de.get_sample_times_before_t0()), solution_points[:101], ls='-', color='k', alpha=0.7)
plt.plot(np.array(de.get_sample_times_after_t0()[1:]), solution_points[101:], ls='-', color='k', alpha=0.7)

plt.show()