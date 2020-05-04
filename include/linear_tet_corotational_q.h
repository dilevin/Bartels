#ifndef SIM_linear_tetcorotational_q_H
#define SIM_linear_tetcorotational_q_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <psi_stretch_F.h>
#include <psi_corotational_S.h>

namespace sim {

template<typename DefoType, typename DerivedV, typename Scalar, typename ParamType>
auto linear_tet_corotational_q(const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
              const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<ParamType> &params, const Scalar &volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_corotational_q.cpp>
#endif

#endif