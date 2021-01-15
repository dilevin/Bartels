#ifdef SIM_STATIC_LIBRARY
# include<../include/psi_muscle_fiber_F.h>
#endif

template<typename DefoType, typename DerivedV, typename ParameterType>
typename DefoType::Scalar sim::psi_muscle_fiber_F(const Eigen::MatrixBase<DefoType> &F, const Eigen::DenseBase<DerivedV> &direction, const  Eigen::MatrixBase<ParameterType> &params) {

    //material parameters are just the stiffness of the zero-length fiber spring
    return 0.5*params(0)*direction.transpose()*(F.transpose()*F)*direction;
}

