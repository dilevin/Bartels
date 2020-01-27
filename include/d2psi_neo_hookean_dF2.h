#ifndef SIM_D2PSI_NEO_HOOKEAN_DF2_H
#define SIM_D2PSI_NEO_HOOKEAN_DF2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename HessianType, typename ParameterType>
    void d2psi_neo_hookean_dF2(Eigen::DenseBase<HessianType> &ddw, Eigen::DenseBase<HessianType> &F, ParameterType &&C, ParameterType &&D) {
            
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/d2psi_neo_hooean_dF2.cpp>
#endif

#endif