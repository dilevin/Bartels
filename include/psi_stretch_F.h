
#ifndef SIM_PSI_STRETCH_F_H
#define SIM_PSI_STRETCH_F_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename DefoType, typename DpsiStretchFunc, typename ParameterType>
    typename DefoType::Scalar psi_stretch_F(const Eigen::MatrixBase<DefoType> &F, DpsiStretchFunc psi, const Eigen::MatrixBase<ParameterType> &params);
        
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/psi_stretch_F.cpp>
#endif

#endif


