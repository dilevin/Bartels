#ifndef SIM_LINEAR_TETMESH_NEOHOOKEAN_DQ_H
#define SIM_LINEAR_TETMESH_NEOHOOKEAN_DQ_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tet_neohookean_dq.h>


namespace sim {

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, typename Scalar>
void linear_tetmesh_neohookean_dq(Eigen::MatrixBase<DerivedRet> &g, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        Eigen::MatrixBase<DefoType> &dXinv, Eigen::MatrixBase<DerivedVol>  &volume, Scalar C, Scalar D);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_neohookean_dq.cpp>
#endif

#endif