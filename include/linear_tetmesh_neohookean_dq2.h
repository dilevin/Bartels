#ifndef SIM_LINEAR_TETMESH_NEOHOOKEAN_DQ2_H
#define SIM_LINEAR_TETMESH_NEOHOOKEAN_DQ2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tet_neohookean_dq2.h>


namespace sim {

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, typename DerivedParam1, typename DerivedParam2>
void linear_tetmesh_neohookean_dq2(Eigen::SparseMatrix<DerivedRet> &H, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam1> &C, const Eigen::MatrixBase<DerivedParam2> &D);



}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_neohookean_dq2.cpp>
#endif

#endif