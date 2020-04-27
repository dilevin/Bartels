cmake_minimum_required (VERSION 3.2)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project (bartles_tests C CXX)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})


set(CMAKE_CXX_STANDARD 17)

include(../cmake/bartels.cmake)

include_directories(${bartels_INCLUDE_DIR})

#executables for tests
add_executable(test_flatten_multiply test_flatten_multiply.cpp)
target_link_libraries(test_flatten_multiply PUBLIC bartels)

add_executable(test_assemble test_assemble.cpp)
target_link_libraries(test_assemble PUBLIC bartels)

add_executable(test_block_diagonal test_block_diagonal.cpp)
target_link_libraries(test_block_diagonal PUBLIC bartels)

add_executable(test_constitutive_model test_constitutive_model.cpp)
target_link_libraries(test_constitutive_model PUBLIC bartels)

add_executable(test_omp test_omp.cpp)
target_link_libraries(test_omp PUBLIC bartels)
#/usr/local/opt/intel/compilers_and_libraries/mac/mkl/lib/libmkl_intel_lp64.dylib /usr/local/opt/intel/compilers_and_libraries/mac/mkl/lib/libmkl_intel_thread.dylib /usr/local/opt/intel/compilers_and_libraries/mac/mkl/lib/libmkl_core.dylib /usr/local/opt/intel/compilers_and_libraries/mac/mkl/lib/libmkl_lapack95_lp64.a /usr/local/opt/intel/compilers_and_libraries/mac/mkl/lib/libmkl_blas95_lp64.a
target_compile_options(test_omp PUBLIC -DNDEBUG  -mavx2 -march=native -Ofast)
#add_definitions(-DEIGEN_USE_MKL_ALL -DMKL_DIRECT_CALL)

add_executable(test_pardiso test_pardiso.cpp)
target_link_libraries(test_pardiso PUBLIC bartels)

