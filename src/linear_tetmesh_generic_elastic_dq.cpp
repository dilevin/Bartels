#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_generic_elastic_dq.h>
#endif

template<   typename DerivedRet, 
            typename DerivedV, 
            typename DerivedQ, 
            typename DefoType, 
            typename FType, 
            typename DerivedVol, 
            typename ... Param, 
            typename MatFunc,
            class ElementMatrixCallback,
            typename Enable>
void sim::linear_tetmesh_generic_elastic_dq(Eigen::VectorXx<DerivedRet> &g, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<FType> &F,
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        MatFunc &mat_func,
                                        const ElementMatrixCallback func,
                                        const Param& ... params) 
{

    auto assemble_func = [&q, &func, &mat_func](auto &g,  auto &e, 
                            const auto &F,
                            const auto &dphidX,
                            const auto &volume, const auto & ... params) 
                           { 
                             mat_func(g, q, e, F, sim::unflatten<4,3>(dphidX), params ..., volume(0));
                             func(g); //callback stuff
                           };
    

    Eigen::Vector12x<DerivedRet> gtmp;
    sim::assemble(g, 3*V.rows(), E, E, assemble_func, gtmp, F, dphidX, volume, params ...);
}

