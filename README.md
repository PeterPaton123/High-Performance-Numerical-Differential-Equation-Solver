# High Performance Numerical Differential Equation Solver


## Requirements
1. Install g++-10 & gcc-10.
1. Install cmake3.20+ from source

## Setup
1. Check out the repo and the submodules: `git clone --recurse-submodules git@github.com:PeterPaton123/High-Performance-Numerical-Differential-Equation-Solver.git`
2. Set up a virtual environment for python libraries: `python3 -m venv .`
3. Install those python libraries: `pip install -r requirements.txt`
4. Open the virtual environment: `. venv/bin/activate`

## Build
Good introduction to CMake: https://cliutils.gitlab.io/modern-cmake/

1. Create a directory for build files: `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`

## Run

To run the library in C++:
1. Find the built output files: `cd build/src/`
2. Run `./main.cpp`

To use the C++ library to solve a differential equation and plot the results in python:
1. Provide the differential equation to the example_de function in the python program (build/src/Example.py)
2. Optionally provide a solution (if known) to check accuracy of the picard iterates, as outlined in the python file
3. Run the program: 'python3 Example.py'
