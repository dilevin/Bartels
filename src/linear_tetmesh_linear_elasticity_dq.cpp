#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_linear_elasticity_dq.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, 
         typename DerivedParam, typename ElementMatrixCallback>
void sim::linear_tetmesh_linear_elasticity_dq(Eigen::VectorXx<DerivedRet> &out, Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params,
                                        const ElementMatrixCallback func) {

    auto assemble_func = [&q, &func](auto &H,  auto &e, 
                            const auto &dXinv,
                            const auto &volume, const auto &params) 
                           { 
                             linear_tet_linear_elasticity_dq(H, q, e, sim::unflatten<4,3>(dXinv), params, volume(0));
                             func(H); //callback stuff
                           };
    

    Eigen::Vector12x<DerivedRet> Htmp;
    sim::assemble(out, 3*V.rows(), E, E, assemble_func, Htmp, dXinv, volume, params);
}

