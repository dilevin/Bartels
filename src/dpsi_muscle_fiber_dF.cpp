#ifdef SIM_STATIC_LIBRARY
# include<../include/dpsi_muscle_fiber_dF.h>
#endif

template<typename GradientType, typename DefoType, typename DerivedV, typename ParameterType>
void sim::dpsi_muscle_fiber_dF(Eigen::MatrixBase<GradientType> &dw, const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<DerivedV> &direction ,const Eigen::MatrixBase<ParameterType> &params) {

    Eigen::Matrix<typename DefoType::Scalar, 3,9> D = flatten_multiply_right<Eigen::Matrix3d>(direction);
    
    dw = params(0)*(D.transpose()*D)*flatten(F);
}