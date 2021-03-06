#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2dmesh_linear_elasticity_dq2.h>
#endif

template<typename DerivedRet, int Options, typename StorageIndex, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, 
         typename DerivedParam, 
         typename ElementMatrixCallback>
void sim::linear_tri2dmesh_linear_elasticity_dq2(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &H, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params,
                                        const ElementMatrixCallback func) {

    auto assemble_func = [&q, &func](auto &H,  auto &e, 
                            const auto &dphidX,
                            const auto &volume, const auto &params) 
                           { 
                             linear_tri2d_linear_elasticity_dq2(H, q, e, sim::unflatten<3,2>(dphidX), params, volume(0));
                             func(H); //callback stuff
                           };
    

    Eigen::Matrix6x<DerivedRet> Htmp;
    sim::assemble(H, 2*V.rows(), 2*V.rows(), E, E, assemble_func, Htmp, dphidX, volume, params);
}

#include <iostream>

