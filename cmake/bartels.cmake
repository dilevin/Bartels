#this file setups up targets
#can be imported into other projects to use bartels

# Bartels Options
option(bartels_USE_STATIC_LIBRARY "Use libigl as static library" OFF)

set(bartels_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(bartels_SOURCE_DIR "${bartels_ROOT}")
set(bartels_INCLUDE_DIR ${bartels_ROOT}/include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${bartels_SOURCE_DIR}/cmake)

option(bartels_USE_OPENMP OFF)
option(bartels_USE_MKL OFF)

find_package(LIBIGL REQUIRED)

if(bartels_USE_OPENMP)
    find_package(OpenMP REQUIRED)
endif()

#Just doing MKL right now
#Note: Make sure MKLROOT environment variable is set
if(bartels_USE_MKL)
  
    if(bartels_USE_OPENMP)
        set(BLA_VENDOR Intel10_64lp)
    else()
        set(BLA_VENDOR Intel10_64lp_seq)
    endif()

    find_package(BLAS REQUIRED)

    # #setup the include directories and link libraries
    if(BLAS_FOUND)
        include_directories($ENV{MKLROOT}/include)
        add_definitions(-DEIGEN_USE_MKL_ALL -DMKL_DIRECT_CALL)
    else() 
        message(WARNING "MKL not found")
    endif()
 endif()

# Dependencies are linked as INTERFACE targets unless libigl is compiled as a static library
if(bartels_USE_STATIC_LIBRARY)
    
    file(GLOB SOURCES_bartels "${bartels_SOURCE_DIR}/src/*.cpp")

    add_library(bartels STATIC ${SOURCES_bartels})
    
    if(MSVC)
        target_compile_options(bartels PRIVATE /w) # disable all warnings (not ideal but...)
    else()
        #target_compile_options(${module_libname} PRIVATE -w) # disable all warnings (not ideal but...)
    endif()
else()
    add_library(bartels INTERFACE)
endif()


#prepreprocessor definition for static library 
if(bartels_USE_STATIC_LIBRARY)
    target_include_directories(bartels PUBLIC ${bartels_INCLUDE_DIR})
    target_compile_definitions(bartels INTERFACE -DSIM_STATIC_LIBRARY)
else()
    target_include_directories(bartels INTERFACE ${bartels_INCLUDE_DIR})
endif()

target_compile_definitions(bartels INTERFACE -DSIM_DATA_DIRECTORY=${bartels_ROOT}/data)
target_link_libraries(bartels INTERFACE igl::core)

if(OpenMP_CXX_FOUND)

    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        execute_process(
            COMMAND brew --prefix libomp 
            RESULT_VARIABLE BREW_OMP
            OUTPUT_VARIABLE BREW_OMP_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        include_directories(${BREW_OMP_PREFIX}/include)
        target_link_libraries(bartels INTERFACE OpenMP::OpenMP_CXX)
    elseif()
        include_directories(${OpenMP_CXX_INCLUDE_DIRS})
        target_link_libraries(bartels INTERFACE OpenMP::OpenMP_CXX)
    endif()

    target_compile_definitions(bartels INTERFACE -DBARTELS_USE_OPENMP)
    
endif()

if(bartels_USE_MKL)
    target_link_libraries(bartels INTERFACE ${BLAS_LIBRARIES})
endif()