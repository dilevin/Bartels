#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_generic_elastic_q.h>
#endif

template<typename DerivedV, 
         typename DerivedQ, 
         typename DefoType, 
         typename FType,
         typename DerivedVol,
         typename MatFunc,
         typename ...Params>
auto sim::linear_tetmesh_generic_elastic_q(const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<FType> &F, 
                                        const Eigen::MatrixBase<DefoType> &dphidX, 
                                        const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        MatFunc &mat_func,
                                        const Params& ... params) {

    auto assemble_func = [&q, &mat_func](auto &e, 
                            const auto &F,
                            const auto &dphidX,
                            const auto &volume, const auto &...params) 
                           { 
                             return mat_func(q, e, F, sim::unflatten<4,3>(dphidX), params..., volume(0));
                           };
    

    return sim::assemble(E, assemble_func, F, dphidX, volume, params...);
}
