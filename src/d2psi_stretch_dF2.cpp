#ifdef SIM_STATIC_LIBRARY
# include<../include/d2psi_stretch_dF2.h>
#endif

#include <igl/svd3x3.h>

template<typename HessianType, typename DefoType, typename DpsiStretchFunc, typename D2psiStretchFunc, typename ParameterType>
void sim::d2psi_stretch_dF2(Eigen::MatrixBase<HessianType> &ddw, const Eigen::MatrixBase<DefoType> &F, DpsiStretchFunc dpsi, D2psiStretchFunc d2psi,const Eigen::MatrixBase<ParameterType> &params) {

    using Scalar = typename HessianType::Scalar;

    Eigen::Matrix3x<float> F_float,U,V;
    Eigen::Vector3x<float> S;
    Eigen::Tensor3333x<float> dU, dV;
    Eigen::Tensor333x<float> dS;
    Eigen::Vector3x<float> PlamVec; 
    Eigen::Vector3x<float> Plam; 
    Eigen::Matrix3x<float> Plam2; 

    F_float = F.template cast<float>();
    igl::svd3x3(F_float,U,S,V);
    
    //derivative of SVD wrt to F
    //check multiplicity, small random permutation if eigenvalues not unique
    if(std::fabs(S[0] - S[1]) < 1e-5 || std::fabs(S[1] - S[2]) < 1e-5 || std::fabs(S[0] - S[2]) < 1e-5) {
        F_float += Eigen::Matrix3x<float>::Random()*1e-5;
        igl::svd3x3(F_float,U,S,V);
    }
    
    dpsi(Plam, S, params);
    d2psi(Plam2, S, params);
    
    dsvd(dU, dS, dV, U, S, V);
    Eigen::Matrix3x<Scalar> rowMat;
    
    //This formatting is quite complicated
    for(unsigned int r = 0; r <3; ++r) {
        for(unsigned int s = 0; s<3; ++s) {
            PlamVec  = Plam2*dS[r][s];
            rowMat = (dU[r][s]*Plam.asDiagonal()*V.transpose() + U*Plam.asDiagonal()*dV[r][s].transpose() + U*PlamVec.asDiagonal()*V.transpose()).template cast<Scalar>();
            rowMat.transposeInPlace();
            ddw.row(3*r + s) = Eigen::Map<Eigen::Matrix<Scalar, 1,9> >(rowMat.data(), 9);
            
        }
    }

}
