#ifndef SIM_LINEAR_NEOHOOKEAN_Q_H
#define SIM_LINEAR_NEOHOOKEAN_Q_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <psi_neohookean_F.h>

namespace sim {

template<typename DefoType, typename DerivedV, typename  ParamType, typename Scalar>
auto linear_tet_neohookean_q(const Eigen::MatrixBase<DerivedV> &q, Eigen::Ref<const Eigen::RowVectorXi> element,  
                            const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<ParamType> &params, Scalar volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_neohookean_q.cpp>
#endif

#endif 