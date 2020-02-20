cmake_minimum_required (VERSION 3.2)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project (bartels_utils C CXX)

include(../cmake/bartels.cmake)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})


set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

#executables for tests
add_executable(gen_ele_mat_model ${PROJECT_SOURCE_DIR}/src/gen_ele_mat_model.cpp )
target_compile_definitions(gen_ele_mat_model PUBLIC -DJSON_DIRECTORY=${PROJECT_SOURCE_DIR}/json -DBARTELS_SRC_DIRECTORY=${bartels_ROOT})
