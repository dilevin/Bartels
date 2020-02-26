#ifndef SIM_DSVD_H
#define SIM_DSVD_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <dsvd.h>

namespace sim {

    //computes derivative of SVD and stores in tensor variables 
    //matrix valued [r][s] tensor entry is the derivative of that quantity with respect to F(r,s)
    template<typename Scalar, typename UType, typename SType, typename VType>
    void dsvd(Eigen::Tensor3333x<Scalar> &dU, Eigen::Tensor333x<Scalar>  &dS, Eigen::Tensor3333x<Scalar> &dV, const Eigen::Matrix3x<UType> &U, const Eigen::Vector3x<SType> &S, const Eigen::Matrix3x<VType> &V);

    
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/dsvd.cpp>
#endif

#endif

#include <Eigen/Dense>
#include <EigenTypes.h>


