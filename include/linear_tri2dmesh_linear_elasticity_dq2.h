#ifndef SIM_LINEAR_TRI2DMESH_LINEAR_ELASTICITY_DQ2_H
#define SIM_LINEAR_TRI2DMESH_LINEAR_ELASTICITY_DQ2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tri2d_linear_elasticity_dq2.h>


namespace sim {

//some c++ trickery to allow for default call backs 
auto default_callback = [](auto &element_matrix){};

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, 
         typename DerivedParam1, typename DerivedParam2,
         class ElementMatrixCallback = decltype(default_callback)>
void linear_tri2dmesh_linear_elasticity_dq2(Eigen::SparseMatrix<DerivedRet> &H, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam1> &YM, const Eigen::MatrixBase<DerivedParam2> &mu,
                                        const ElementMatrixCallback func = default_callback);



}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2dmesh_linear_elasticity_dq2.cpp>
#endif

#endif