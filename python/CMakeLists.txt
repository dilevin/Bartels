cmake_minimum_required (VERSION 3.2)

project (bartels_python)

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../mex )
#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../mex )
#set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../mex )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../cmake ${PROJECT_SOURCE_DIR}/../extern/numpyeigen/cmake)
set(CMAKE_CXX_STANDARD 17)

#Disable OpenMP because I need to use a MATLAB specific setup to get this to work
if (bartels_USE_OPENMP)
	set(bartels_MATLAB_USE_OPENMP ON)
else()
	set(bartels_MATLAB_USE_OPENMP OFF)
endif()

set(bartels_USE_OPENMP OFF CACHE BOOL "Override option" FORCE)
set(bartels_USE_MKL OFF CACHE BOOL "Override option" FORCE)

include(${CMAKE_SOURCE_DIR}/../extern/numpyeigen/cmake/numpyeigen.cmake)
include(${CMAKE_SOURCE_DIR}/../cmake/bartels.cmake)

file(GLOB PYTHON_SOURCES *.cpp)

npe_add_module(bartelspy
  BINDING_SOURCES
  ${PYTHON_SOURCES})

include_directories(${bartels_INCLUDE_DIR} ./include ${CMAKE_SOURCE_DIR}/../extern/numpyeigen/src)
target_link_libraries(bartelspy PRIVATE npe bartels)

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