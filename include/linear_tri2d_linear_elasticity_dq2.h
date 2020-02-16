#ifndef SIM_LINEAR_TRI2D_LINEAR_ELASTICITY_HESSIAN_H
#define SIM_LINEAR_TRI2D_LINEAR_ELASTICITY_HESSIAN_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <d2psi_linear_elasticity_de2.h>

namespace sim {

template<typename HessianType, typename DefoType, typename DerivedV, typename  Scalar>
void linear_tri2d_linear_elasticity_dq2(Eigen::DenseBase<HessianType> &H, const Eigen::MatrixBase<DerivedV> &q, Eigen::Ref<const Eigen::RowVectorXi> element,  
                                        const Eigen::MatrixBase<DefoType> &dXinv, Scalar YM, Scalar mu, Scalar volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2d_linear_elasticity_dq2.cpp>
#endif

#endif 