#ifdef SIM_STATIC_LIBRARY
# include<../include/psi_stretch_F.h>
#endif

#include <igl/svd3x3.h>

template<typename DefoType, typename DpsiStretchFunc, typename ParameterType>
typename DefoType::Scalar sim::psi_stretch_F(const Eigen::MatrixBase<DefoType> &F, DpsiStretchFunc psi, const Eigen::MatrixBase<ParameterType> &params) {

        
    using Scalar = typename DefoType::Scalar;

    Eigen::Matrix3x<float> F_float,U,V;
    Eigen::Vector3x<float> S;
    
    F_float = F.template cast<float>();
    
    igl::svd3x3(F_float,U,S,V);

    //evaluate energy
    return static_cast<Scalar>(psi(S,params));
}

