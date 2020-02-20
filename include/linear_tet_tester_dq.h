#ifndef SIM_linear_tettester_dq_H
#define SIM_linear_tettester_dq_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <d2psi_tester_dF.h>

namespace sim {

template<typename HessianType, typename DefoType, typename DerivedV, typename Scalar, typename ...Params>
void linear_tet_tester_dq(Eigen::DenseBase<HessianType> &out, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, const Scalar &volume, const Params ... &params) {

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tettester_dq.cpp>
#endif

#endif