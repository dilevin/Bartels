#ifdef SIM_STATIC_LIBRARY
# include<../include/psi_corotational_S.h>
#endif

template<typename SType, typename ParameterType>
SType sim:: psi_corotational_S(const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params) {
    
    return params(1)*((S[0] - 1.) * (S[0] - 1.) + (S[1] - 1.) * (S[1] - 1.) + (S[2] - 1.) * (S[2] - 1.) ) + 0.5*params(0)*(S[0] + S[1] + S[2] - 3.0)*( S[0] + S[1] + S[2] - 3.0);
}

