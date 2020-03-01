#ifndef SIM_PSI_ARAP_S_H
#define SIM_PSI_ARAP_S_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename SType, typename ParameterType>
    SType psi_arap_S(const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params);
    
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/psi_arap_S.cpp>
#endif

#endif



