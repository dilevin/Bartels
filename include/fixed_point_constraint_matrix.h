#ifndef SIM_FIXED_POINT_CONSTRAINT_MATRIX_H
#define SIM_FIXED_POINT_CONSTRAINT_MATRIX_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

namespace sim {
    template<typename RetType, int Options, typename StorageIndex, typename DerivedV>
    void fixed_point_constraint_matrix(Eigen::SparseMatrix<RetType, Options, StorageIndex> &P, const Eigen::MatrixBase<DerivedV> &V, Eigen::Ref<const Eigen::VectorXi> fixed_indices);
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/fixed_point_constraint_matrix.cpp>
#endif

#endif
