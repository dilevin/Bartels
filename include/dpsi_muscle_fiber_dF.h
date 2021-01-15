#ifndef SIM_DPSI_MUSCLE_FIBER_DF_H
#define SIM_DPSI_MUSCLE_FIBER_DF_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename GradientType, typename DefoType, typename DerivedV, typename ParameterType>
    void dpsi_muscle_fiber_dF(Eigen::MatrixBase<GradientType> &dw, const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<DerivedV> &direction ,const Eigen::MatrixBase<ParameterType> &params);
        
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/dpsi_muscle_fiber_dF.cpp>
#endif

#endif