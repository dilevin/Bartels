#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2dmesh_neohookean_dq2.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, 
         typename DerivedParam1, typename DerivedParam2,
         typename ElementMatrixCallback>
void sim::linear_tri2dmesh_neohookean_dq2(Eigen::SparseMatrix<DerivedRet> &H, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam1> &C, const Eigen::MatrixBase<DerivedParam2> &D,
                                        const ElementMatrixCallback func) {

    auto assemble_func = [&q, &func](auto &H,  auto &e, 
                            const auto &dXinv,
                            const auto &volume, const auto &C, const auto &D) 
                           { 
                             linear_tri2d_neohookean_dq2(H, q, e, sim::unflatten<3,2>(dXinv), C(0), D(0), volume(0));
                             func(H); //callback stuff
                           };
    

    Eigen::Matrix6x<DerivedRet> Htmp;
    sim::assemble(H, 2*V.rows(), 2*V.rows(), E, E, assemble_func, Htmp, dXinv, volume, C, D);
}

#include <iostream>

