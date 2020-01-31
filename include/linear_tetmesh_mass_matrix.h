#ifndef SIM_LINEAR_TETMESH_MASS_MATRIX_H
#define SIM_LINEAR_TETMESH_MASS_MATRIX_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tet_mass_matrix.h>

namespace sim {

template<typename DerivedRet, typename  DerivedV, typename DerivedVol>
void linear_tetmesh_mass_matrix(Eigen::SparseMatrix<DerivedRet> &M, Eigen::DenseBase<DerivedV> &V, Eigen::Ref<Eigen::MatrixXi> E, 
                                Eigen::MatrixBase<DerivedVol>  &density, Eigen::MatrixBase<DerivedVol>  &volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_mass_matrix.cpp>
#endif

#endif 