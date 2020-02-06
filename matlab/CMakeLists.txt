cmake_minimum_required (VERSION 3.2)

project (bartels_matlab)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../cmake)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_SOURCE_DIR}/../cmake/bartels.cmake)

find_package(Matlab REQUIRED)
include_directories(${bartels_INCLUDE_DIR} ${Matlab_INCLUDE_DIRS})

file(GLOB BARTELS_MATLAB_SRCS ${CMAKE_SOURCE_DIR}/*.cpp)

foreach( file ${BARTELS_MATLAB_SRCS})
	get_filename_component(name ${file} NAME)
	
	matlab_add_mex(NAME ${name} 
			SRC ${file}
			LINK_TO ${Matlab_MX_LIBRARY} ${Matlab_MEX_LIBRARY} bartels
			OUTPUT_NAME ${name})
    

endforeach( file BARTELS_MATLAB_SRCS )


