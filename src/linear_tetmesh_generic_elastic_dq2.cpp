#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_generic_elastic_dq2.h>
#endif

//void sim::linear_tetmesh_mass_matrix(Eigen::SparseMatrix<DerivedRet> &M, const Eigen::MatrixBase<DerivedV> &V, Eigen::Ref<Eigen::MatrixXi> E, 
//                                    Eigen::MatrixBase<DerivedVol>  &density,  Eigen::MatrixBase<DerivedVol>  &volume) {

template<typename DerivedRet, int Options, typename StorageIndex, 
         typename DerivedV, 
         typename DerivedQ, 
         typename FType,
         typename DefoType,
         typename DerivedVol, 
         typename MatFunc,
         typename ...Params,
         typename ElementMatrixCallback,
         typename Enable>
void sim::linear_tetmesh_generic_elastic_dq2(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &H, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<FType> &F,
                                        const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        MatFunc &mat_func,
                                        const ElementMatrixCallback func,
                                        const Params& ... params) {

    auto assemble_func = [&q, &func, &mat_func](auto &H,  auto &e, 
                            const auto &F,
                            const auto &dphidX,
                            const auto &volume, const auto &...params) 
                           { 
                             mat_func(H, q, e, sim::unflatten<3,3>(F), sim::unflatten<4,3>(dphidX), params..., volume(0));
                             func(H); //callback stuff
                           };
    

    Eigen::Matrix12d Htmp;
    sim::assemble(H, 3*V.rows(), 3*V.rows(), E, E, assemble_func, Htmp, F, dphidX, volume, params...);
}

