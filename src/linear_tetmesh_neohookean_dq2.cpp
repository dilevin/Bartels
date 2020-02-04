#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_neohookean_dq2.h>
#endif

//void sim::linear_tetmesh_mass_matrix(Eigen::SparseMatrix<DerivedRet> &M, Eigen::DenseBase<DerivedV> &V, Eigen::Ref<Eigen::MatrixXi> E, 
//                                    Eigen::MatrixBase<DerivedVol>  &density,  Eigen::MatrixBase<DerivedVol>  &volume) {

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, typename Scalar>
void sim::linear_tetmesh_neohookean_dq2(Eigen::SparseMatrix<DerivedRet> &H, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        Eigen::MatrixBase<DefoType> &dXinv, Eigen::MatrixBase<DerivedVol>  &volume, Scalar C, Scalar D) {

    auto assemble_func = [&C, &D, &q](auto &H,  auto &e, 
                            auto &dXinv,
                            auto &volume) 
                           { 
                             linear_tet_neohookean_dq2(H, q, e, sim::unflatten<4,3>(dXinv), C, D, volume(0));
                           };
    

    Eigen::Matrix12d Htmp;
    sim::assemble(H, 3*V.rows(), 3*V.rows(), E, E, assemble_func, Htmp, dXinv, volume);
}

#include <iostream>

