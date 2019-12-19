cmake_minimum_required (VERSION 3.2)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project (bartles_tests C CXX)

set(CMAKE_CXX_STANDARD 17)

#include Eigen
include_directories(${PROJECT_SOURCE_DIR}/../extern/Eigen)
#include library files
include_directories(${PROJECT_SOURCE_DIR}/../include)

#executables for tests
add_executable(test_flatten_multiply test_flatten_multiply.cpp)
add_executable(test_assemble test_assemble.cpp)
