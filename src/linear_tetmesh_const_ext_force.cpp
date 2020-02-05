#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_const_ext_force.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DerivedVol, typename DerivedT>
void sim::linear_tetmesh_const_ext_force(Eigen::MatrixBase<DerivedRet> &f, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<Eigen::MatrixXi> E, 
                                         Eigen::MatrixBase<DerivedVol>  &volume, Eigen::MatrixBase<DerivedT> &traction) {

    auto assemble_func = [&traction](auto &f,  auto &e, auto &volume) 
                           { 
                             linear_tet_const_ext_force(f, e, volume(0), traction) {
                             linear_tet_neohookean_dq2(g, q, e, sim::unflatten<4,3>(dXinv), C, D, volume(0));
                           };
    

    Eigen::Vector12x<typename DerivedRet::Scalar> g_tmp;
    sim::assemble(g, 3*V.rows(), E, E, assemble_func, g_tmp, volume);
}

#include <iostream>

