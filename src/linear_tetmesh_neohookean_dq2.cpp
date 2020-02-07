#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_neohookean_dq2.h>
#endif

//void sim::linear_tetmesh_mass_matrix(Eigen::SparseMatrix<DerivedRet> &M, Eigen::DenseBase<DerivedV> &V, Eigen::Ref<Eigen::MatrixXi> E, 
//                                    Eigen::MatrixBase<DerivedVol>  &density,  Eigen::MatrixBase<DerivedVol>  &volume) {

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, typename DerivedParam1, typename DerivedParam2>
void sim::linear_tetmesh_neohookean_dq2(Eigen::SparseMatrix<DerivedRet> &H, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam1> &C, const Eigen::MatrixBase<DerivedParam2> &D) {

    auto assemble_func = [&q](auto &H,  auto &e, 
                            const auto &dXinv,
                            const auto &volume, const auto &C, const auto &D) 
                           { 
                             linear_tet_neohookean_dq2(H, q, e, sim::unflatten<4,3>(dXinv), C(0), D(0), volume(0));
                           };
    

    Eigen::Matrix12d Htmp;
    sim::assemble(H, 3*V.rows(), 3*V.rows(), E, E, assemble_func, Htmp, dXinv, volume, C, D);
}

#include <iostream>

