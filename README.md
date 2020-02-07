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
    
 Here is an example of using Bartels to compute the first 20 deformation modes of a Neo-Hookean bunny:
 
    >> [V,T,F] = readMESH('/Users/dilevin/Documents/Research/Development/bartels/data/meshes_mesh/coarser_bunny.mesh');
    >> M = linear_tetmesh_mass_matrix(V,T, 0.1*ones(size(T,1),1), vol);
    >> [lambda, mu] = emu_to_lame(6e5, 0.4);
    >> H = linear_tetmesh_neohookean_dq2(V,T, reshape(V', 3*size(V,1), 1), dX, vol, 0.5*lambda*ones(size(T,1),1), 0.5*mu*ones(size(T,1),1));
    >> [modes, freq] = eigs(-H, M, 20, 'smallestabs');
    
 **NOTE:** I use [GPToolbox](https://github.com/alecjacobson/gptoolbox) by Alec Jacobson for file I/O (i.e readMESH) and geometry processing. 
