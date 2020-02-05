#ifndef SIM_LINEAR_NEOHOOKEAN_DQ_H
#define SIM_LINEAR_NEOHOOKEAN_DQ_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <dpsi_neohookean_dF.h>

namespace sim {

template<typename GradientType, typename DefoType, typename DerivedV, typename  Scalar>
void linear_tet_neohookean_dq2(Eigen::DenseBase<GradientType> &g, const Eigen::MatrixBase<DerivedV> &q, Eigen::Ref<const Eigen::RowVectorXi> element,  
                                        const Eigen::MatrixBase<DefoType> &dXinv, Scalar C, Scalar D, Scalar volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_neohookean_dq.cpp>
#endif

#endif 