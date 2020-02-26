#ifndef SIM_D2PSI_STRETCH_DF2_H
#define SIM_D2PSI_STRETCH_DF2_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <dsvd.h>

namespace sim {

    template<typename HessianType, typename DefoType, typename DpsiStretchFunc, typename D2psiStretchFunc, typename ParameterType>
    void d2psi_stretch_dF2(Eigen::MatrixBase<HessianType> &ddw, const Eigen::MatrixBase<DefoType> &F, DpsiStretchFunc dpsi, D2psiStretchFunc d2psi,const Eigen::MatrixBase<ParameterType> &params);
    
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/d2psi_stretch_dF2.cpp>
#endif

#endif