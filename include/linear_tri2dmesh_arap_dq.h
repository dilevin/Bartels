#ifndef SIM_linear_tri2dmesh_arap_dq_H
#define SIM_linear_tri2dmesh_arap_dq_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tri2d_arap_dq.h>


namespace sim {

//some c++ trickery to allow for default call backs 
auto default_callback = [](auto &element_matrix){};

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, 
         typename DerivedParam, class ElementMatrixCallback = decltype(default_callback)>
void linear_tri2dmesh_arap_dq(Eigen::VectorXx<DerivedRet> &H, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params,
                                        const ElementMatrixCallback func = default_callback);



}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2dmesh_arap_dq.cpp>
#endif

#endif
