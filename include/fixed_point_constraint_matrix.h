#ifndef SIM_FIXED_POINT_CONSTRAINT_MATRIX_H
#define SIM_FIXED_POINT_CONSTRAINT_MATRIX_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

namespace sim {
    template<typename RetType, typename DerivedV>
    void fixed_point_constraint_matrix(Eigen::SparseMatrix<RetType> &P, Eigen::DenseBase<DerivedV> &V, Eigen::Ref<const Eigen::VectorXi> fixed_indices);
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/fixed_point_constraint_matrix.cpp>
#endif

#endif
