#ifndef SIM_LINEAR_TETMESH_GENERIC_ELASTIC_DQ2_H
#define SIM_LINEAR_TETMESH_GENERIC_ELASTIC_DQ2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <assemble.h>

namespace sim {

//some c++ trickery to allow for default call backs 
template<typename DerivedRet, int Options, typename StorageIndex, 
         typename DerivedV, 
         typename DerivedQ, 
         typename FType,
         typename DefoType, 
         typename DerivedVol, 
         typename MatFunc,
         typename ... Params, 
         class ElementMatrixCallback,
         typename Enable = typename Eigen::enable_if_not_eigen<ElementMatrixCallback>::type>
void linear_tetmesh_generic_elastic_dq2(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &H, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<FType> &F,
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        MatFunc &mat_func,
                                        const ElementMatrixCallback func,
                                        const  Params& ... params);


template<typename DerivedRet, int Options, typename StorageIndex, 
         typename DerivedV, 
         typename DerivedQ, 
         typename FType,
         typename DefoType, 
         typename DerivedVol, 
         typename MatFunc,
         typename ... Params>
void linear_tetmesh_generic_elastic_dq2(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &H, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<FType> &F,
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        MatFunc &mat_func,
                                        const  Params& ... params) 
{

    linear_tetmesh_generic_elastic_dq2(H, V,  E, q, F, dphidX, volume, mat_func, default_callback, params ...);                                        
}


}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tetmesh_generic_elastic_dq2.cpp>
#endif

#endif