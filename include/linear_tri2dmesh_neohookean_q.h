#ifndef SIM_linear_tri2dmesh_neohookean_q_H
#define SIM_linear_tri2dmesh_neohookean_q_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tri2d_neohookean_q.h>


namespace sim {

template<typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, typename DerivedParam>
auto linear_tri2dmesh_neohookean_q(Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params);



}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2dmesh_neohookean_q.cpp>
#endif

#endif
