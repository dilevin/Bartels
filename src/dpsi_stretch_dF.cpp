#ifdef SIM_STATIC_LIBRARY
# include<../include/dpsi_stretch_dF.h>
#endif

#include <igl/svd3x3.h>

template<typename HessianType, typename DefoType, typename DpsiStretchFunc, typename ParameterType>
void sim::dpsi_stretch_dF(Eigen::MatrixBase<HessianType> &ddw, const Eigen::MatrixBase<DefoType> &F, DpsiStretchFunc dpsi, const Eigen::MatrixBase<ParameterType> &params) {

    using Scalar = typename HessianType::Scalar;

    Eigen::Vector3x<float> Plam;
    Eigen::Matrix3x<float> F_float, U,V;
    Eigen::Vector3x<float> S;

    F_float = F.template cast<float>();
    igl::svd3x3(F_float,U,S,V);
    
    //Fix for inverted elements (thanks to Danny Kaufman)
    Scalar det = S.determinant();
    
    if(det <= -1e-10)
    {
        if(S[0] < 0) S[0] *= -1;
        if(S[1] < 0) S[1] *= -1;
        if(S[2] < 0) S[2] *= -1;
    }
    
    if(U.determinant() <= 0)
    {
        U(0, 2) *= -1;
        U(1, 2) *= -1;
        U(2, 2) *= -1;
    }
    
    if(V.determinant() <= 0)
    {
        V(0, 2) *= -1;
        V(1, 2) *= -1;
        V(2, 2) *= -1;
    }
    
    dpsi(Plam, S, params);
    ddw = (flatten(U*(Plam.asDiagonal()*V.transpose()))).template cast<Scalar>();
                        
}
