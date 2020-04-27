cmake_minimum_required (VERSION 3.2)

project (bartels_matlab)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../mex )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../mex )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../mex )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../cmake)
set(CMAKE_CXX_STANDARD 17)

#Disable OpenMP because I need to use a MATLAB specific setup to get this to work
if (bartels_USE_OPENMP)
	set(bartels_MATLAB_USE_OPENMP ON)
else()
	set(bartels_MATLAB_USE_OPENMP OFF)
endif()

set(bartels_USE_OPENMP OFF CACHE BOOL "Override option" FORCE)
set(bartels_USE_MKL OFF CACHE BOOL "Override option" FORCE)

include(${CMAKE_SOURCE_DIR}/../cmake/bartels.cmake)

find_package(Matlab REQUIRED)
include_directories(${bartels_INCLUDE_DIR} ${Matlab_INCLUDE_DIRS})

#MATLAB OpenMP directory which is needed to allow openmp usage in MEX files
#It OS specific
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(Matlab_OMP_LIB "${Matlab_ROOT_DIR}/sys/os/glnxa64/libiomp5.so")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(Matlab_OMP_LIB "${Matlab_ROOT_DIR}/sys/os/maci64/libiomp5.dylib")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(Matlab_OMP_LIB "${Matlab_ROOT_DIR}/bin/win64/libiomp5md.lib")
endif()

message(${Matlab_OMP_LIB})
file(GLOB BARTELS_MATLAB_SRCS ${CMAKE_SOURCE_DIR}/*.cpp)

#compiler options
if(bartels_MATLAB_USE_OPENMP)
	find_package(OpenMP)
	if(OpenMP_CXX_FOUND)
		
		if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
			#Assuming libomp has been installed via homebrew (brew install libomp)
			include_directories("/usr/local/Cellar/libomp/10.0.0/include")
			set(OpenMP_CXX_FLAGS -Xpreprocessor -fopenmp)
		endif()

		target_compile_definitions(bartels INTERFACE -DBARTELS_USE_OPENMP)

	endif()

	#I need to remove any openmp libraries added by mkl as they can conflict with
	#matlabs OpenMP
	if(bartels_USE_MKL)
		get_target_property(LINKED_LIBS bartels INTERFACE_LINK_LIBRARIES)
		LIST(FILTER LINKED_LIBS EXCLUDE REGEX libiomp5.dylib)
		set_target_properties(bartels PROPERTIES INTERFACE_LINK_LIBRARIES "${LINKED_LIBS}")
	endif()

endif()


foreach( file ${BARTELS_MATLAB_SRCS})
	get_filename_component(name ${file} NAME_WE)
	
	matlab_add_mex(NAME ${name} 
			SRC ${file}
			LINK_TO ${Matlab_MX_LIBRARY} ${Matlab_MEX_LIBRARY} ${Matlab_OMP_LIB} bartels
			OUTPUT_NAME ${name})

	if(bartels_MATLAB_USE_OPENMP)
		target_compile_options(${name} PUBLIC ${OpenMP_CXX_FLAGS})
		target_link_options(${name} PUBLIC ${OpenMP_CXX_FLAGS})
	endif()
	

endforeach( file BARTELS_MATLAB_SRCS )


