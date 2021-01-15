#ifndef SIM_LINEAR_TETMESH_F_H
#define SIM_LINEAR_TETMESH_F_H

#include <Eigen/Dense>
#include <EigenTypes.h>
#include <eval_at_point.h>

namespace sim {

    template<typename DerivedRet, typename DerivedV, typename DerivedDPhi>
    void linear_tetmesh_F(Eigen::DenseBase<DerivedRet> &F, Eigen::Ref<const Eigen::MatrixXi> E, const Eigen::MatrixBase<DerivedV> &q, const Eigen::DenseBase<DerivedDPhi> &dphidX); 

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_F.cpp>
#endif

#endif