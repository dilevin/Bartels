#ifndef SIM_SEARCH_DIRECTION_NEWTON_SPARSE_H
#define SIM_SEARCH_DIRECTION_NEWTON_SPARSE_H

#include <Eigen/SparseLU>

namespace sim {

    template<typename DerivedG, typename Scalar, int StorageOptions, typename StorageIndex, class SparseLinearSolver=Eigen::SparseLU<Eigen::SparseMatrix<Scalar, StorageOptions, StorageIndex> > >
    bool search_direction_newton_sparse(Eigen::DenseBase<DerivedG> &d, 
                                const Eigen::DenseBase<DerivedG> &g, 
                                const Eigen::SparseMatrix<Scalar, StorageOptions, StorageIndex> &H, 
                                SparseLinearSolver &solver);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/search_direction_newton_sparse.cpp>
#endif

#endif 