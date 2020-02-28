#ifdef SIM_STATIC_LIBRARY
# include<../include/psi_neohookean_F.h>
#endif

template<typename DefoType, typename ParameterType>
typename DefoType::Scalar sim::psi_neohookean_F(const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params) {

    using Scalar = typename DefoType::Scalar;
    Scalar detF = F.determinant();
    Scalar J23 = stablePow(detF,2.0);
    J23=1.0/J23;
    Eigen::Matrix<Scalar, 3,3> Cbar = J23*F.transpose()*F;
    
    return params(0)*(Cbar.trace() - 3.0) + params(1)*(detF - 1)*(detF - 1);
}

