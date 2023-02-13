#include <npe.h>

//bartels
#include <linear_tetmesh_mass_matrix.h>

npe_function(linear_tetmesh_mass_matrix)
npe_arg(V, dense_float, dense_double)
npe_arg(E, dense_int)
npe_arg(densities, npe_matches(V))
npe_arg(volumes, npe_matches(V))
npe_begin_code()

    Eigen::SparseMatrix<npe_Scalar_V> M;
    Eigen::Matrix<npe_Scalar_V, Eigen::Dynamic, 1> densities_vec = densities.col(0);
    Eigen::Matrix<npe_Scalar_V, Eigen::Dynamic, 1> volumes_vec = volumes.col(0);

    sim::linear_tetmesh_mass_matrix(M, V, E, densities_vec, volumes_vec);

    return npe::move(M);

npe_end_code()