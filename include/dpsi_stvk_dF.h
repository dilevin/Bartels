#ifndef SIM_DPSI_STVK_DF_H
#define SIM_DPSI_STVK_DF_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename GradientType, typename DefoType, typename ParameterType>
    void dpsi_stvk_dF(Eigen::MatrixBase<GradientType> &dw, const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params);
        
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/dpsi_stvk_dF.cpp>
#endif

#endif