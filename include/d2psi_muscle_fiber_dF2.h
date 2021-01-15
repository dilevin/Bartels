#ifndef SIM_D2PSI_MUSCLE_FIBER_DF2_H
#define SIM_D2PSI_MUSCLE_FIBER_DF2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename HessianType, typename DefoType, typename DerivedV, typename ParameterType>
    void d2psi_muscle_fiber_dF2(Eigen::MatrixBase<HessianType> &ddw, const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<DerivedV> &direction, const Eigen::MatrixBase<ParameterType> &params);
            
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/d2psi_muscle_fiber_dF2.cpp>
#endif

#endif