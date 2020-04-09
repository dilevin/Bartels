
#ifndef SIM_LINEAR_TETMESH_CONST_EXT_FORCE_H
#define SIM_LINEAR_TETMESH_CONST_EXT_FORCE_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <linear_tetmesh_dphi_dX.h>
#include <assemble.h>

namespace sim {
    
    template<typename DerivedRet, typename DerivedV>
    void linear_tetmesh_B(Eigen::SparseMatrix<DerivedRet> &B, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E);
}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_B.cpp>
#endif

#endif