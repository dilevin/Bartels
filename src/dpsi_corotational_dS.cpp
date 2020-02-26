
#ifdef SIM_STATIC_LIBRARY
# include<../include/dpsi_corotational_dS.h>
#endif

template<typename OutputType, typename SType, typename ParameterType>
void sim::dpsi_corotational_dS(Eigen::Vector3x<OutputType> &ds, const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params) {
            
    ds[0] = 2.0*params[1]*(-1.0+S[0])+params[0]*(-3.0+S[0]+S[1]+S[2]);
    ds[1] = 2.0*params[1]*(-1.0+S[1])+params[0]*(-3.0+S[0]+S[1]+S[2]);
    ds[2] = 2.0*params[1]*(-1.0+S[2])+params[0]*(-3.0+S[0]+S[1]+S[2]);

}

