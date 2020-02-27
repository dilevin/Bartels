#ifndef SIM_D2PSI_STVK_DF2_H
#define SIM_D2PSI_STVK_DF2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename GradientType, typename DefoType, typename ParameterType>
    void d2psi_stvk_dF2(Eigen::MatrixBase<GradientType> &dw, const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params);
        
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/d2psi_stvk_dF2.cpp>
#endif

#endif