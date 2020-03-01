#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_stvk_q.h>
#endif

template<typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol,typename DerivedParam>
auto sim::linear_tetmesh_stvk_q(Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params) {

    auto assemble_func = [&q](auto &e, 
                            const auto &dXinv,
                            const auto &volume, const auto &params) 
                           { 
                             return linear_tet_stvk_q(q, e, sim::unflatten<4,3>(dXinv), params, volume(0));
                           };
    

    return sim::assemble(E, assemble_func, dXinv, volume, params);
}
