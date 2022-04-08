set(CXX /usr/bin/g++)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

project(HP-numerical-DE-solver)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Og -ggdb -g3 -fno-omit-frame-pointer")

add_subdirectory(src)