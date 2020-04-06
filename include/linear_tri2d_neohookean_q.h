#ifndef SIM_linear_tri2dneohookean_q_H
#define SIM_linear_tri2dneohookean_q_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <psi_neohookean_F.h>

namespace sim {

template<typename DefoType, typename DerivedV, typename Scalar, typename ParamType>
auto linear_tri2d_neohookean_q(const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
              const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<ParamType> &params, const Scalar &volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2d_neohookean_q.cpp>
#endif

#endif