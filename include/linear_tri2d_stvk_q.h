#ifndef SIM_linear_tri2dstvk_q_H
#define SIM_linear_tri2dstvk_q_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <psi_stvk_F.h>

namespace sim {

template<typename DefoType, typename DerivedV, typename Scalar, typename ParamType>
auto linear_tri2d_stvk_q(const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
              const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<ParamType> &params, const Scalar &volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2d_stvk_q.cpp>
#endif

#endif