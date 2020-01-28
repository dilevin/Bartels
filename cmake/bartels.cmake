#this file setups up targets
#can be imported into other projects to use bartels

# Bartels Options
option(bartels_USE_STATIC_LIBRARY "Use libigl as static library" OFF)

set(bartels_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(bartels_SOURCE_DIR "${bartels_ROOT}")
set(bartels_INCLUDE_DIR ${bartels_ROOT}/include ${bartels_SOURCE_DIR}/extern/Eigen)

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