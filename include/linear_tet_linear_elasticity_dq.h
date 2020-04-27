#ifndef SIM_linear_tetlinear_elasticity_dq_H
#define SIM_linear_tetlinear_elasticity_dq_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <dpsi_linear_elasticity_de.h>

namespace sim {

template<typename HessianType, typename DefoType, typename DerivedV, typename Scalar, typename DerivedParams>
void linear_tet_linear_elasticity_dq(Eigen::DenseBase<HessianType> &out, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedParams> &params, const Scalar &volume);
}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_linear_elasticity_dq.cpp>
#endif

#endif