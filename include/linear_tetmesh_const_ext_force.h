#ifndef SIM_LINEAR_TETMESH_CONST_EXT_FORCE_H
#define SIM_LINEAR_TETMESH_CONST_EXT_FORCE_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>
#include <linear_tet_const_ext_force.h>


namespace sim {

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DerivedVol, typename DerivedT>
void linear_tetmesh_const_ext_force(Eigen::MatrixBase<DerivedRet> &f, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<Eigen::MatrixXi> E, 
                                         Eigen::MatrixBase<DerivedVol>  &volume, Eigen::MatrixBase<DerivedT> &traction); 


}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_neohookean_dq.cpp>
#endif

#endif