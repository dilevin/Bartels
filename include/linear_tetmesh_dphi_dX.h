#ifndef SIM_LINEAR_TETMESH_INVERSE_DX_H
#define SIM_LINEAR_TETMESH_INVERSE_DX_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <eval_at_point.h>
#include <linear_tet_dphi_dX.h>


namespace sim {

template<typename DerivedRet, typename DerivedV>
void linear_tetmesh_dphi_dX(Eigen::MatrixXx<DerivedRet> &dX, const Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E); 

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_dphi_dX.cpp>
#endif

#endif