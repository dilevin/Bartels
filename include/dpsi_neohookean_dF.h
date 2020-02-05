#ifndef SIM_DPSI_NEO_HOOKEAN_DF_H
#define SIM_DPSI_NEO_HOOKEAN_DF_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename GradientType, typename DefoType, typename ParamterType, typename ParameterType>
    void dpsi_neo_hookean_dF(Eigen::MatrixBase<GradientType> &dw, const Eigen::MatrixBase<DefoType> &F, ParameterType C, ParameterType D);
        
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/dpsi_neohookean_dF.cpp>
#endif

#endif