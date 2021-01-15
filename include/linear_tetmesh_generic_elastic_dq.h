#ifndef SIM_LINEAR_TETMESH_GENERIC_DQ_H
#define SIM_LINEAR_TETMESH_GENERIC_DQ_H

#include <Eigen/Dense>
#include <EigenTypes.h>
#include <assemble.h>

namespace sim {

template<   typename DerivedRet, 
            typename DerivedV, 
            typename DerivedQ, 
            typename DefoType, 
            typename FType, 
            typename DerivedVol, 
            typename ... Params, 
            typename MatFunc,
            class ElementMatrixCallback,
            typename Enable = typename Eigen::enable_if_not_eigen<ElementMatrixCallback>::type > //
void linear_tetmesh_generic_elastic_dq(Eigen::VectorXx<DerivedRet> &g, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<FType> &F, 
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        MatFunc &mat_func,
                                        const ElementMatrixCallback func,
                                        const Params& ... params);



template<   typename DerivedRet, 
            typename DerivedV, 
            typename DerivedQ, 
            typename DefoType, 
            typename FType, 
            typename DerivedVol, 
            typename ... Params, 
            typename MatFunc>
inline void linear_tetmesh_generic_elastic_dq(Eigen::VectorXx<DerivedRet> &g, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<FType> &F, 
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        MatFunc &mat_func,
                                        const Params& ... params) {

    linear_tetmesh_generic_elastic_dq(g, V,  E, q, F, dphidX, volume, mat_func, default_callback, params ...);                                        
}

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_generic_elastic_dq.cpp>
#endif

#endif
