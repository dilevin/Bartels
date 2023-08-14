
#include <npe.h>

//bartels
#include <linear_tri2dmesh_B.h>

npe_function(linear_tri2dmesh_B)
npe_arg(V, dense_float, dense_double)
npe_arg(E, dense_int)
npe_begin_code()

    Eigen::SparseMatrix<npe_Scalar_V> B;
    sim::linear_tri2dmesh_B(B, V, E);

    return npe::move(B);

npe_end_code()