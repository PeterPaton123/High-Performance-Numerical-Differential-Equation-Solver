project(HP-numerical-DE-solver)

pybind11_add_module(HP_Numerical_DE_Solver DifferentialEquationSolverLib.cpp DifferentialEquationSolver.cpp)

set(SOURCE_FILES main.cpp DifferentialEquationSolver.cpp)

add_executable(main ${SOURCE_FILES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Example.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})