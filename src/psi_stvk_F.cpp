#ifdef SIM_STATIC_LIBRARY
# include<../include/psi_stvk_F.h>
#endif

template<typename DefoType, typename ParameterType>
typename DefoType::Scalar sim::psi_stvk_F(const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params) {

    using Scalar = typename DefoType::Scalar;

    // std::cout<<"Stvk Energy"<<std::endl;
    Eigen::Matrix<Scalar, 3,3> E = 0.5*(F.transpose()*F - Eigen::Matrix<Scalar,3,3>::Identity());
    return 2.0*params(0)*(E*E).trace() + params(1)*E.trace()*E.trace();
}

