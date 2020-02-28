#ifndef SIM_PSI_NEO_HOOKEAN_F_H
#define SIM_PSI_NEO_HOOKEAN_F_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename DefoType, typename ParameterType>
    typename DefoType::Scalar psi_neohookean_F(const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params);
            
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/psi_neohookean_F.cpp>
#endif

#endif