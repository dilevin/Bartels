#ifndef SIM_LINEAR_NEOHOOKEAN_DQ_H
#define SIM_LINEAR_NEOHOOKEAN_DQ_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <dpsi_neohookean_dF.h>

namespace sim {

template<typename GradientType, typename DefoType, typename DerivedV, typename  ParamType, typename Scalar>
void linear_tet_neohookean_dq(Eigen::DenseBase<GradientType> &g, const Eigen::MatrixBase<DerivedV> &q, Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<ParamType> &params, Scalar volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_neohookean_dq.cpp>
#endif

#endif 