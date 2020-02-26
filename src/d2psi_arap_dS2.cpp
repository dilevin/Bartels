
#ifdef SIM_STATIC_LIBRARY
# include<../include/d2psi_arap_dS2.h>
#endif

template<typename OutputType, typename SType, typename ParameterType>
void sim::d2psi_arap_dS2(Eigen::Matrix3x<OutputType> &ds, const Eigen::Vector3x<SType>  &S, const Eigen::MatrixBase<ParameterType> &params) {
                      
    ds.setIdentity();
    ds *= static_cast<OutputType>(2)*params(0);
    
}




            
