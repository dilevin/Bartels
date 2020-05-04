#ifndef SIM_LINEAR_TRI3DMESH_INVERSE_DX_H
#define SIM_LINEAR_TRI3DMESH_INVERSE_DX_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <eval_at_point.h>
#include <linear_tri3d_dphi_dX.h>


namespace sim {

template<typename DerivedRet, typename DerivedV>
void linear_tri3dmesh_dphi_dX(Eigen::MatrixXx<DerivedRet> &dX, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E); 

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri3dmesh_dphi_dX.cpp>
#endif

#endif