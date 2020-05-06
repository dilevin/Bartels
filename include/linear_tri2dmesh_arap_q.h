#ifndef SIM_linear_tri2dmesh_arap_q_H
#define SIM_linear_tri2dmesh_arap_q_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tri2d_arap_q.h>


namespace sim {

template<typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, typename DerivedParam>
auto linear_tri2dmesh_arap_q(const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params);



}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2dmesh_arap_q.cpp>
#endif

#endif
