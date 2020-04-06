#ifdef SIM_STATIC_LIBRARY
# include<../include/psi_stvk_F.h>
#endif

template<typename DefoType, typename ParameterType>
typename DefoType::Scalar sim::psi_stvk_F(const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params) {

    using Scalar = typename DefoType::Scalar;

    // std::cout<<"Stvk Energy"<<std::endl;
    Eigen::Matrix<Scalar, 3,3> E = 0.5*(F.transpose()*F - Eigen::Matrix<Scalar,3,3>::Identity());
    return params(1)*(E*E).trace() + 0.5*params(0)*E.trace()*E.trace();
}

