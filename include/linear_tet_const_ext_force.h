#ifndef SIM_LINEAR_TET_CONST_EXT_FORCE_H
#define SIM_LINEAR_TET_CONST_EXT_FORCE_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

template<typename VectorType, typename TractionType, typename ScalarType>
void linear_tet_const_ext_force(Eigen::DenseBase<VectorType> &f, Eigen::Ref<const Eigen::RowVectorXi> element, const ScalarType volume, const Eigen::DenseBase<TractionType> &traction);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_const_ext_force.cpp>
#endif

#endif 