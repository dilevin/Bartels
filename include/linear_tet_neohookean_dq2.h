#ifndef SIM_LINEAR_NEOHOOKEAN_HESSIAN_H
#define SIM_LINEAR_NEOHOOKEAN_HESSIAN_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <d2psi_neohookean_dF2.h>

namespace sim {

template<typename HessianType, typename DefoType, typename DerivedV, typename  Scalar>
void linear_tet_neohookean_dq2(Eigen::DenseBase<HessianType> &H, const Eigen::MatrixBase<DerivedV> &q, Eigen::Ref<const Eigen::RowVectorXi> element,  
                                        const Eigen::MatrixBase<DefoType> &dXinv, Scalar C, Scalar D, Scalar volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_neohookean_dq2.cpp>
#endif

#endif 