#ifndef SIM_LINEAR_TETMESH_GENERIC_Q_H
#define SIM_LINEAR_TETMESH_GENERIC_Q_H

#include <Eigen/Dense>
#include <EigenTypes.h>
#include <assemble.h>

namespace sim {

    template<typename DerivedV, 
             typename DerivedQ, 
             typename DefoType, 
             typename FType,
             typename DerivedVol,
             typename MatFunc,
             typename ... Params>
    auto linear_tetmesh_generic_elastic_q(const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<FType> &F, 
                                        const Eigen::MatrixBase<DefoType> &dphidX, 
                                        const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        MatFunc &mat_func,
                                        const Params& ... params);



}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_generic_elastic_q.cpp>
#endif

#endif