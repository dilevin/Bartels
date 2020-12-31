#ifdef SIM_STATIC_LIBRARY
# include<../include/search_direction_newton_sparse.h>
#endif

template<typename DerivedG, typename Scalar, int StorageOptions, typename StorageIndex, class SparseLinearSolver>
bool sim::search_direction_newton_sparse(Eigen::DenseBase<DerivedG> &d, 
                                         const Eigen::DenseBase<DerivedG> &g, 
                                         const Eigen::SparseMatrix<Scalar, StorageOptions, StorageIndex> &H,
                                         SparseLinearSolver &solver) {

    
    solver.compute(H);

    if(solver.info()!=Eigen::Success) {
        return false;
    }
    
    d = solver.solve(-g);
    
    if(solver.info()!=Eigen::Success) {
        return false;
    }

    return true; 

}
