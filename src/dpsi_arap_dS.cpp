
#ifdef SIM_STATIC_LIBRARY
# include<../include/dpsi_arap_dS.h>
#endif

template<typename OutputType, typename SType, typename ParameterType>
void sim::dpsi_arap_dS(Eigen::Vector3x<OutputType> &ds, const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params) {
            
    ds[0] = static_cast<OutputType>(2)*params(0) * (S[0] - static_cast<OutputType>(1));
    ds[1] = static_cast<OutputType>(2)*params(0) * (S[1] - static_cast<OutputType>(1));
    ds[2] = static_cast<OutputType>(2)*params(0) * (S[2] - static_cast<OutputType>(1));
}

               
                