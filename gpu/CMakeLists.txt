cmake_minimum_required (VERSION 3.2)

project (bartels_gpu LANGUAGES CUDA CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../cmake ${PROJECT_SOURCE_DIR}/../extern/numpyeigen/cmake)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED True)

#Disable OpenMP because I need to use a MATLAB specific setup to get this to work
if (bartels_USE_OPENMP)
	set(bartels_MATLAB_USE_OPENMP ON)
else()
	set(bartels_MATLAB_USE_OPENMP OFF)
endif()

set(bartels_USE_OPENMP OFF CACHE BOOL "Override option" FORCE)
set(bartels_USE_MKL OFF CACHE BOOL "Override option" FORCE)

include(${CMAKE_SOURCE_DIR}/../cmake/bartels.cmake)

file(GLOB GPU_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

include_directories(${bartels_INCLUDE_DIR} ./include /usr/local/cuda/include)
add_library(bartelsgpu ${GPU_SOURCES})

target_link_libraries(bartelsgpu PRIVATE bartels)

#just a test for now
add_executable(test_init ${CMAKE_SOURCE_DIR}/examples/init_sparse_matrix.cpp)
target_link_libraries(test_init PRIVATE bartelsgpu)

# Sort projects inside the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	foreach(config ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${config} config)
		string(REPLACE /MD /MT CMAKE_C_FLAGS_${config} "${CMAKE_C_FLAGS_${config}}")
    string(REPLACE /MD /MT CMAKE_CXX_FLAGS_${config} "${CMAKE_CXX_FLAGS_${config}}")
    # LIST(APPEND CMAKE_CXX_FLAGS_${config} "/Zm")
	endforeach()
endif()

