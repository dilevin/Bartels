#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_neohookean_dq.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, typename Scalar>
void sim::linear_tetmesh_neohookean_dq(Eigen::MatrixBase<DerivedRet> &g, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        Eigen::MatrixBase<DefoType> &dXinv, Eigen::MatrixBase<DerivedVol>  &volume, Scalar C, Scalar D) {

    auto assemble_func = [&C, &D, &q](auto &g,  auto &e, 
                            auto &dXinv,
                            auto &volume) 
                           { 
                             linear_tet_neohookean_dq2(g, q, e, sim::unflatten<4,3>(dXinv), C, D, volume(0));
                           };
    

    Eigen::Vector12x<typename DerivedRet::Scalar> g_tmp;
    sim::assemble(g, 3*V.rows(), E, E, assemble_func, g_tmp, dXinv, volume);
}

#include <iostream>

