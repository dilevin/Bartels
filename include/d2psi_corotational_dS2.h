#ifndef SIM_D2PSI_COROTATIONAL_DS2_H
#define SIM_D2PSI_COROTATIONAL_DS2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename OutputType, typename SType, typename ParameterType>
    void d2psi_corotational_dS2(Eigen::Matrix3x<OutputType> &ds, const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params);
    
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/d2psi_corotational_dS2.cpp>
#endif

#endif