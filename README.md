# Bartels

A lightweight collection of routines for physics simulation .

### External Dependencies  ###
Intel MKL (OPTIONAL)
Pardiso (OPTIONAL)
OpenMP (OPTIONAL)

### Included Submodules (Installed Automatically) ###
1. Libigl https://github.com/libigl/libigl
2. Eigen >= 3.2 (By Default Bartels uses the libigl Eigen install)

> **To get started:** Clone this repository and all its [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) dependencies using:
> 
>     git clone --recursive https://github.com/dilevin/Bartels.git

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
    >> YM = 2e6; %in Pascals
    >> pr =  0.45
    >> [lambda, mu] = emu_to_lame(YM*ones(size(T,1),1), pr*ones(size(T,1),1));
    >>  H = linear_tetmesh_neohookean_dq2(V,T, q, dX, vol, [0.5*mu, 0.5*lambda]);
    >> [modes, freq] = eigs(-H, M, 20, 'smallestabs');
    
 **NOTE:** I use [GPToolbox](https://github.com/alecjacobson/gptoolbox) by Alec Jacobson for file I/O (i.e readMESH) and geometry processing. 
 
## Conventions
I try to obey some naming conventions when I implement new functions in Bartels which makes it, in some sense, self documenting. Below are some of these conventions:

* Finite element methods are prefaced by element type *i.e linear_tet_....* indicates this method applies to a single tetrahedral element with linear shape functions.

* There are seperate methods which apply per element functions to an entire computational mesh. These take the form *i.e. linear_tetmesh_...*

* **q** refers to the degrees of freedom of a mechanical system, no matter what they are. For FEM they are the vertices of the simulation mesh

* **F** refers to the deformation gradient at  point in space

* **psi** refers to a potential energy function for a constitutive model

* **phi** referes to shape functions

* lower case d is used to represent differential operations. 

* when taking derivatives with respect to matrix quantities (like **F**), the matrix quantitiy is flattened to a column vector. *i.e the 3x3 matrix **F** = [F00 F01 F02; F10 F11 F12; F20 F21 F22] becomes a 9x1 vector [F00 F10 F20 F01 F11 F21 F02 F12 F22]'.

Some examples of putting it all together:

* dpsi_neohookean_dF2 computes the second derivative of the neohookean potential energy, with respect to the deformation gradient.

* linear_tet_dphi_dX computes the derivative of the linear tetrahedron shape functions with respect to the reference space

* linear_tetmesh_dphi_dX computes the above over the entire tetmesh

* linear_tetmesh_neohooken_dq2 computes the sparse Hessian of the neohookean energy over an entire tetmesh

* linear_tetmesh_stvk_dq computes the gradient of the stvk energy over an entire tetmesh

* linear_tetmesh_arap_q computes the energy of the As-Rigid-As-Possible energy  over an entire tetmesh

## Installation Instructions for Optional Dependencies

### OpenMP

Bartels can leverage the OpenMP library for parallelization (though honestly, most functions aren't parallelized yet). On *non-OSX* computers with an OpenMP compantible compiler, you simply need to call cmake with the **bartels_USE_OPENMP** option set to on. So, from the build directory:

>
>   cmake .. -Dbartels_USE_OPENMP=ON

#### OpenMP on OSX

**IMPORTANT:** Requires CMake 3.17 or above 

The osx native compiler doesn't support OpenMP by default. Fortunately this support can be added using the [Homebrew package manager](https://brew.sh).

1. Install Homebrew from [https://brew.sh](https://brew.sh)
2. Run 'brew install libomp'
3. From the build directory run `cmake .. -Dbartels_USE_OPENMP=ON`

### Pardiso

Bartels now comes with an Eigen wrapper for the open source version of the [Pardiso linear systems solver](https://pardiso-project.org).

To use Pardiso visit the [webpage]((https://pardiso-project.org) and request a license. Once you recieve your license email, download the pardiso library.

1. mkdir ${BARTELS_SOURCE_DIRECTORY}/extern/pardiso
2. Copy **libPardiso** to ${BARTELS_SOURCE_DIRECTORY}/extern/pardiso
3. Create Pardiso.lic in ${BARTELS_SOURCE_DIRECTORY}/extern/pardiso
4. Paste your license key into Pardiso.lic
5. From ${BARTELS_SOURCE_DIRECTORY}/build run `cmake .. -Dbartels_USE_OPENMP=ON -Dbartels_USE_PARDISO=ON`

**IMPORTANT:** Pardiso requires OpenMP

### Intel MKL`

Bartels relies on the [Eigen](https://eigen.tuxfamily.org) library for linear algebra operations. Eigen itself can be accelerated by linking to the [Intel Math Kernel Library (MKL)](https://software.intel.com/en-us/performance-libraries). **It's available free for academic use**. Bartels can be compiled to use MKL to speed up basic linear algebra operations.

1. Download and install the [Intel Math Kernel Library (MKL)](https://software.intel.com/en-us/performance-libraries)
2. Set the **MKLROOT** Environment Variable to the fullpath of the mkl installation directory (on my machine this is *usr/local/opt/intel/compilers_and_libraries/mac/mkl*).
3. From ${BARTELS_SOURCE_DIRECTORY}/build run `cmake .. -Dbartels_USE_MKL=ON`

**IMPORTANT:** OpenMP, Pardiso and MKL can all be used together as well by specifying all options as ON.

**IMPORTANT 2:** MKL is not compatible with MATLAB, if you are building the MATLAB interface, **DO NOT** turn on MKL.

