#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_arap_dq.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, 
         typename DerivedParam, typename ElementMatrixCallback>
void sim::linear_tetmesh_arap_dq(Eigen::VectorXx<DerivedRet> &out, Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params,
                                        const ElementMatrixCallback func) {

    auto assemble_func = [&q, &func](auto &H,  auto &e, 
                            const auto &dphidX,
                            const auto &volume, const auto &params) 
                           { 
                             linear_tet_arap_dq(H, q, e, sim::unflatten<4,3>(dphidX), params, volume(0));
                             func(H); //callback stuff
                           };
    

    Eigen::Vector12x<DerivedRet> Htmp;
    sim::assemble(out, 3*V.rows(), E, E, assemble_func, Htmp, dphidX, volume, params);
}

