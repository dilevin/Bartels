#ifndef SIM_DPSI_LINEAR_ELASTICITY_DE_H
#define SIM_DPSI_LINEAR_ELASTICITY_DE_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename HessianType, typename DerivedStrain, typename ParameterType>
    void dpsi_linear_elasticity_de(Eigen::MatrixBase<HessianType> &C,  const Eigen::MatrixBase<DerivedStrain> &strain, const Eigen::MatrixBase<ParameterType> &params);
            
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/d2psi_linear_elasticity_de.cpp>
#endif

#endif