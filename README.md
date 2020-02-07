# Bartels

A lightweight collection of routines for physics simulation.

### External Dependencies  ###
None so far

### Included Submodules (Installed Automatically) ###
1. Libigl https://github.com/libigl/libigl
2. Eigen >= 3.2 (By Default Bartels uses the libigl Eigen install)

> **To get started:** Clone this repository and all its [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) dependencies using:
> 
>     git clone --recursive https://github.com/dilevin/https://github.com/dilevin/bartels.git

## Compilation
Bartels is a header only library but includes somethings that need to be compiled or use.

### Tests
To compile the included tests do the following:

    cd ${BARTELS_SOURCE_DIRECTORY}/tests
    mkdir build
    cd build
    cmake ..
    make all
    
### MATLAB Interface
Bartels includes MATLAB wrappers for usefull functions. To compile the MATLAB wrappers do the following:

    cd ${BARTELS_SOURCE_DIRECTORY}/matlab
    mkdir build
    cd build
    cmake ..
    make all

To enable Bartels in MATLAB open MATLAB and issue the following commands: 

    addpath('${BARTELS_SOURCE_DIRECTORY}/matlab')
    addpath('${BARTELS_SOURCE_DIRECTORY}/matlab/mex')
    savepath
