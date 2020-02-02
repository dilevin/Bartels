cmake_minimum_required (VERSION 3.2)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project (bartles_tests C CXX)

set(CMAKE_CXX_STANDARD 17)

include(../cmake/bartels.cmake)

include_directories(${bartels_INCLUDE_DIR})

message(WARNING ${bartels_INCLUDE_DIR})

#executables for tests
add_executable(test_flatten_multiply test_flatten_multiply.cpp)
target_link_libraries(test_flatten_multiply igl::core bartels)

add_executable(test_assemble test_assemble.cpp)
target_link_libraries(test_assemble igl::core bartels)

add_executable(test_constitutive_model test_constitutive_model.cpp)
target_link_libraries(test_constitutive_model igl::core bartels)

