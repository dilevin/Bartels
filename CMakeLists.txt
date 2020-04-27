cmake_minimum_required(VERSION 3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Bartels VERSION 1.0 LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
    set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR/cmake}" ${CMAKE_PREFIX_PATH})

    include(${PROJECT_SOURCE_DIR}/cmake/bartels.cmake)
    

