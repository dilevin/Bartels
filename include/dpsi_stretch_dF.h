#ifndef SIM_DPSI_STRETCH_DF_H
#define SIM_DPSI_STRETCH_DF_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <dsvd.h>

namespace sim {

    template<typename HessianType, typename DefoType, typename D2psiStretchFunc, typename DpsiStretchFunc, typename ParameterType>
    void dpsi_stretch_dF(Eigen::MatrixBase<HessianType> &ddw, const Eigen::MatrixBase<DefoType> &F, DpsiStretchFunc &dpsi, const Eigen::MatrixBase<ParameterType> &params);
    
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/dpsi_stretch_dF.cpp>
#endif

#endif