#ifndef SIM_linear_tri2darap_dq_H
#define SIM_linear_tri2darap_dq_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <dpsi_arap_dS.h>
#include <dpsi_stretch_dF.h>


namespace sim {

template<typename HessianType, typename DefoType, typename DerivedV, typename Scalar, typename ParamType>
void linear_tri2d_arap_dq(Eigen::DenseBase<HessianType> &out, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<ParamType> &params, const Scalar &volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2d_arap_dq.cpp>
#endif

#endif