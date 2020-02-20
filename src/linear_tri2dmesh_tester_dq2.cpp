#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2dmesh_tester_dq2.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, 
         typename DerivedParam, typename ElementMatrixCallback>
void sim::linear_tri2dmesh_tester_dq2(Eigen::SparseMatrix<DerivedRet> &out, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params,
                                        const ElementMatrixCallback func) {

    auto assemble_func = [&q, &func](auto &H,  auto &e, 
                            const auto &dXinv,
                            const auto &volume, const auto &params) 
                           { 
                             linear_tri2d_tester_dq2(H, q, e, sim::unflatten<3,2>(dXinv), params(0), volume(0));
                             func(H); //callback stuff
                           };
    

    Eigen::Matrix6x<DerivedRet> Htmp;
    sim::assemble(H, 3*V.rows(), 3*V.rows(), E, E, assemble_func, Htmp, dXinv, volume, params);
}

