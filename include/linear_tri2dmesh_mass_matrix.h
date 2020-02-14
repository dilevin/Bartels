#ifndef SIM_LINEAR_TRI2DMESH_MASS_MATRIX_H
#define SIM_LINEAR_TRI2DMESH_MASS_MATRIX_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tri2d_mass_matrix.h>

namespace sim {

template<typename DerivedRet, typename  DerivedV, typename DerivedVol>
void linear_tri2dmesh_mass_matrix(Eigen::SparseMatrix<DerivedRet> &M, const Eigen::DenseBase<DerivedV> &V, Eigen::Ref<const Eigen::MatrixXi> E, 
                                const Eigen::MatrixBase<DerivedVol>  &density, const Eigen::MatrixBase<DerivedVol>  &volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2dmesh_mass_matrix.cpp>
#endif

#endif 