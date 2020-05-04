#ifdef SIM_STATIC_LIBRARY
# include<../include/dpsi_linear_elasticity_de.h>
#endif

template<typename GradientType, typename DerivedStrain, typename ParameterType>
void sim::dpsi_linear_elasticity_de(Eigen::MatrixBase<GradientType> &C, const Eigen::MatrixBase<DerivedStrain> &strain, const Eigen::MatrixBase<ParameterType> &params) {

    C.setZero();

    typename ParameterType::Scalar YM = params(0);
    typename ParameterType::Scalar mu = params(1);

    C(0,0) = 1.0-mu;
    C(0,1) = mu;
    C(0,2) = mu;
    C(1,0) = mu;
    C(1,1) = 1.0-mu;
    C(1,2) = mu;
    C(2,0) = mu;
    C(2,1) = mu;
    C(2,2) = 1.0-mu;
    C(3,3) = 0.5*(1.0-2.0*mu);
    C(4,4) = 0.5*(1.0-2.0*mu);
    C(5,5) = 0.5*(1.0-2.0*mu);
    C *= (YM/((1.0+mu)*(1.0-2.0*mu)))*strain;

}
