#ifndef SIM_PSI_STVK_F_H
#define SIM_PSI_STVK_F_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename DefoType, typename ParameterType>
    typename DefoType::Scalar psi_stvk_F(const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params);
            
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/psi_stvk_F.cpp>
#endif

#endif