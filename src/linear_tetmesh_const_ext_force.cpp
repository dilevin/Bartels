#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_const_ext_force.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedVol, typename DerivedT>
void sim::linear_tetmesh_const_ext_force(Eigen::VectorXx<DerivedRet>  &f, Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<Eigen::MatrixXi> E, 
                                         Eigen::MatrixBase<DerivedVol>  &volume, const Eigen::MatrixBase<DerivedT> &&traction) {

    auto assemble_func = [&traction](auto &f,  auto &e, auto &volume) 
                           { 
                             linear_tet_const_ext_force(f, e, volume(0), traction);
                           };
    

    Eigen::Vector12x<DerivedRet> g_tmp;
    sim::assemble(f, 3*V.rows(), E, E, assemble_func, g_tmp, volume);

}

#include <iostream>

