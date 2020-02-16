#ifndef SIM_D2PSI_LINEAR_ELASTICITY_DE2_H
#define SIM_D2PSI_LINEAR_ELASTICITY_DE2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename HessianType, typename ParameterType>
    void d2psi_linear_elasticity_de2(Eigen::MatrixBase<HessianType> &C, ParameterType &&YM, ParameterType &&mu);
            
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/d2psi_linear_elasticity_de2.cpp>
#endif

#endif