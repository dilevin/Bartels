
#ifndef SIM_LINEAR_TRI2DMESH_B_H
#define SIM_LINEAR_TRI2DMESH_B_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <linear_tri2dmesh_dphi_dX.h>
#include <assemble.h>

namespace sim {
    
    template<typename DerivedRet, typename DerivedV>
    void linear_tri2dmesh_B(Eigen::SparseMatrix<DerivedRet> &B, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E);
}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tri2dmesh_B.cpp>
#endif

#endif