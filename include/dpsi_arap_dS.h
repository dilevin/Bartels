#ifndef SIM_DPSI_ARAP_DS_H
#define SIM_DPSI_ARAP_DS_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename OutputType, typename SType, typename ParameterType>
    void dpsi_arap_dS(Eigen::Vector3x<OutputType> &ds, const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params);
    
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/dpsi_arap_dS.cpp>
#endif

#endif