#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_mass_matrix.h>
#endif

#include <iostream>

template<typename DerivedRet, int Options, typename StorageIndex, typename  DerivedV, typename DerivedVol>
void sim::linear_tetmesh_mass_matrix(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &M, const Eigen::DenseBase<DerivedV> &V, Eigen::Ref<const Eigen::MatrixXi> E, 
                                     const Eigen::MatrixBase<DerivedVol>  &density,  const Eigen::MatrixBase<DerivedVol>  &volume) {

    using Scalar = typename DerivedV::Scalar;

    //Yuck but I don't know the proper syntax for template lambdas
    auto assemble_func = [](auto &M,  const auto &e, 
                            const auto &density,
                            const auto &volume) 
                           { sim::linear_tet_mass_matrix(M, e, density(0), volume(0)); };
    

    Eigen::Matrix12x<Scalar> Mtmp;

    sim::assemble(M, 3*V.rows(), 3*V.rows(), E, E, assemble_func, Mtmp, density, volume);

}
