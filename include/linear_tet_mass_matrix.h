#ifndef SIM_LINEAR_TET_MASS_MATRIX_H
#define SIM_LINEAR_TET_MASS_MATRIX_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

template<typename MassMatrixType, typename  Scalar>
void linear_tet_mass_matrix(Eigen::DenseBase<MassMatrixType> &M, Eigen::Ref<const Eigen::RowVectorXi> element, Scalar density, Scalar volume);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_mass_matrix.cpp>
#endif

#endif 