cmake_minimum_required (VERSION 3.2)

project (bartles_matlab)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../cmake)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_SOURCE_DIR}/../cmake/bartels.cmake)

find_package(Matlab REQUIRED)
include_directories(${bartels_INCLUDE_DIR} ${Matlab_INCLUDE_DIRS})

matlab_add_mex(NAME linear_tetmesh_mass_matrix 
			SRC linear_tetmesh_mass_matrix.cpp
			LINK_TO ${Matlab_MX_LIBRARY} ${Matlab_MEX_LIBRARY} bartels
			OUTPUT_NAME linear_tetmesh_mass_matrix)