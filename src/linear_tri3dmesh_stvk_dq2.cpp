#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri3dmesh_stvk_dq2.h>
#endif

template<typename DerivedRet, int Options, typename StorageIndex, typename DerivedV, typename DerivedQ, typename DefoType, 
         typename NormalType, typename DNormalType, typename DerivedVol, 
         typename DerivedParam, typename ElementMatrixCallback>
void sim::linear_tri3dmesh_stvk_dq2(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &out, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, 
                                        const Eigen::MatrixBase<NormalType> &N,
                                        const Eigen::MatrixBase<NormalType> &n,
                                        const Eigen::MatrixBase<DNormalType> &dndq,
                                        const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params,
                                        const ElementMatrixCallback func) {

    auto assemble_func = [&q, &func](auto &H,  auto &e, 
                            const auto &dXinv, const auto &N, const auto &n, const auto &dndq,
                            const auto &volume, const auto &params) 
                           { 
                             linear_tri3d_stvk_dq2(H, q, e, sim::unflatten<3,3>(dXinv), N, n, dndq, params, volume(0));
                             func(H); //callback stuff
                           };
    

    Eigen::Matrix9x<DerivedRet> Htmp;
    sim::assemble(out, 3*V.rows(), 3*V.rows(), E, E, assemble_func, Htmp, dXinv, N, n, dndq, volume, params);
}

