#ifdef SIM_STATIC_LIBRARY
# include<../include/d2psi_muscle_fiber_dF2.h>
#endif

template<typename HessianType, typename DefoType, typename DerivedV, typename ParameterType>
void sim::d2psi_muscle_fiber_dF2(Eigen::MatrixBase<HessianType> &ddw, const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<DerivedV> &direction, const Eigen::MatrixBase<ParameterType> &params) {

    auto D = flatten_multiply_right<Eigen::Matrix3d>(direction);
    
    ddw = params(0)*(D.transpose()*D);

}
