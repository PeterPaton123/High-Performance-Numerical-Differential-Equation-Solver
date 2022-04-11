# High-Performance-Numerical-Differential-Equation-Solver


## Requirements
1. Install g++-10 & gcc-10.
1. Install cmake3.20+ from source

## Setup
1. Check out the repo and the submodules: `git clone --recurse-submodules git@github.com:IC3RD/CPP-design-pattern-for-low-latency.git`
2. Set up a virtual environment for python libraries: `python3 -m venv .`
3. Install those python libraries: `pip install -r requirements.txt`
4. Open the virtual environment: `. venv/bin/activate`

## Build
Good introduction to CMake: https://cliutils.gitlab.io/modern-cmake/

Create a directory for build files: `mkdir build`
Move into it and compile the library into it: `cd build`, `cmake ..`, `make`

## Run

To run the library in C++:
`cd build/src/`
`./main.cpp`

To use the C++ library to solve a differential equation and plot the results in python:
1. Provide the differential equation to the python program in build/src/Example.py
2. Run the program: 'python3 Example.py'
