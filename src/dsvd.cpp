#ifdef SIM_STATIC_LIBRARY
#include <dsvd.h>
#endif

template<typename Scalar, typename UType, typename SType, typename VType>
void sim::dsvd(Eigen::Tensor3333x<Scalar> &dU, Eigen::Tensor333x<Scalar>  &dS, Eigen::Tensor3333x<Scalar> &dV, const Eigen::Matrix3x<UType> &U, const Eigen::Vector3x<SType> &S, const Eigen::Matrix3x<VType> &V) {

    Eigen::Matrix3x<Scalar> UVT, tmp;
    Eigen::Matrix3x<Scalar> lambda;
    Eigen::Matrix3x<Scalar> F;

    Scalar w01, w02, w12;
    Scalar d01, d02, d12;
    Scalar tol = 1e-8;
    
    d01 = S(1)*S(1)-S(0)*S(0);
    d02 = S(2)*S(2)-S(0)*S(0);
    d12 = S(2)*S(2)-S(1)*S(1);
     
    //corresponds to conservative solution --- if singularity is detected no angular velocity
    d01 = 1.0/(std::abs(d01) < tol ? std::numeric_limits<double>::infinity() : d01);
    d02 = 1.0/(std::abs(d02) < tol ? std::numeric_limits<double>::infinity() : d02);
    d12 = 1.0/(std::abs(d12) < tol ? std::numeric_limits<double>::infinity() : d12);
    
    for(unsigned int r=0; r<3; ++r) {
        for(unsigned int s =0; s <3; ++s) {
            
            UVT = U.row(r).transpose()*V.row(s);
            
            //Compute dS
            dS[r][s] = UVT.diagonal();
            
            UVT -= dS[r][s].asDiagonal();
            
            tmp  = S.asDiagonal()*UVT + UVT.transpose()*S.asDiagonal();
            w01 = tmp(0,1)*d01;
            w02 = tmp(0,2)*d02;
            w12 = tmp(1,2)*d12;
            tmp << 0, w01, w02,
                    -w01, 0, w12,
                    -w02, -w12, 0;
            
            dV[r][s] = V*tmp;
            
            tmp = UVT*S.asDiagonal() + S.asDiagonal()*UVT.transpose();
            w01 = tmp(0,1)*d01;
            w02 = tmp(0,2)*d02;
            w12 = tmp(1,2)*d12;
            tmp << 0, w01, w02,
            -w01, 0, w12,
            -w02, -w12, 0;
            
            dU[r][s] = U*tmp;
                        
        }
    }
}
