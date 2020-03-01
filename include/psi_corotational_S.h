#ifndef SIM_PSI_COROTATIONAL_S_H
#define SIM_PSI_COROTATIONAL_S_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename SType, typename ParameterType>
    SType psi_corotational_S(const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params);
    
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/psi_corotational_S.cpp>
#endif

#endif



