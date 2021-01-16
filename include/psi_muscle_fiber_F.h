#ifndef SIM_PSI_MUSCLE_FIBER_F_H
#define SIM_PSI_MUSCLE_FIBER_F_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename DefoType, typename DerivedV, typename ParameterType>
    typename DefoType::Scalar psi_muscle_fiber_F(const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<DerivedV> &direction, const Eigen::MatrixBase<ParameterType> &params);
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/psi_muscle_fiber_F.cpp>
#endif

#endif