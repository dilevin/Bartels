#ifndef SIM_SEARCH_DIRECTION_NEWTON_SPARSE_H
#define SIM_SEARCH_DIRECTION_NEWTON_SPARSE_H

#include <Eigen/SparseLU>

namespace sim {

    template<typename DerivedG, typename DerivedH, class SparseLinearSolver=Eigen::SparseLU<Eigen::MatrixBase<DerivedH> > >
    bool search_direction_newton_sparse(Eigen::MatrixBase<DerivedG> &d, 
                                const Eigen::MatrixBase<DerivedG> &g, 
                                const Eigen::MatrixBase<DerivedH> &H, 
                                SparseLinearSolver &solver);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/search_direction_newton_sparse.cpp>
#endif

#endif 