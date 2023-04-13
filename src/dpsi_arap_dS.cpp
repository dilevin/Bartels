
#ifdef SIM_STATIC_LIBRARY
# include<../include/dpsi_arap_dS.h>
#endif

template<typename OutputType, typename SType, typename ParameterType>
void sim::dpsi_arap_dS(Eigen::Vector6x<OutputType> &ds, const Eigen::Vector6x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params) {

    //derivative of ARAP wrt to symmetric stretch matrix
    //0.5*(S[0] -1)^2 + 0.5*(S[1] -1)^2 +   0.5*(S[2] -1)^2 + S[3]^2 + S[4]^2 + S[5]^2       
    
    ds[0] = params(0,0)*(S[0] - static_cast<OutputType>(1));
    ds[1] = params(0,0)*(S[1] - static_cast<OutputType>(1));
    ds[2] = params(0,0)*(S[2] - static_cast<OutputType>(1));
    ds[3] = static_cast<OutputType>(2)*params(0,0)*(S[3]);
    ds[4] = static_cast<OutputType>(2)*params(0,0)*(S[4]);
    ds[5] = static_cast<OutputType>(2)*params(0,0)*(S[5]);


}
   


               
                