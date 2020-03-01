#ifdef SIM_STATIC_LIBRARY
# include<../include/psi_arap_S.h>
#endif

template<typename SType, typename ParameterType>
SType sim:: psi_arap_S(const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params) {
    
     return params(0)*((S[0] - static_cast<SType>(1)) * (S[0] - static_cast<SType>(1)) +
                       (S[1] - static_cast<SType>(1)) * (S[1] - static_cast<SType>(1)) +
                       (S[2] - static_cast<SType>(1)) * (S[2] - static_cast<SType>(1)));
}

