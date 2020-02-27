#ifdef SIM_STATIC_LIBRARY
# include<../include/d2psi_stvk_dF2.h>
#endif

template<typename GradientType, typename DefoType, typename ParameterType>
void sim::d2psi_stvk_dF2(Eigen::MatrixBase<GradientType> &ddw, const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params) {

    using Scalar = typename GradientType::Scalar;

    Scalar lambda = params(0);
    Scalar mu = params(1); 

    Scalar F1_1, F1_2, F1_3, F2_1, F2_2, F2_3, F3_1, F3_2, F3_3;

    F1_1 = F(0,0);
    F1_2 = F(0,1);
    F1_3 = F(0,2);
    F2_1 = F(1,0);
    F2_2 = F(1,1);
    F2_3 = F(1,2);
    F3_1 = F(2,0);
    F3_2 = F(2,1);
    F3_3 = F(2,2);


    ddw(0,0) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F1_1*F1_1)*lambda+mu*((F1_1*F1_1)*3.0+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F3_1*F3_1-1.0);
    ddw(0,1) = mu*(F1_1*F2_1*2.0+F1_2*F2_2+F1_3*F2_3)+F1_1*F2_1*lambda;
    ddw(0,2) = mu*(F1_1*F3_1*2.0+F1_2*F3_2+F1_3*F3_3)+F1_1*F3_1*lambda;
    ddw(0,3) = mu*(F1_1*F1_2*2.0+F2_1*F2_2+F3_1*F3_2)+F1_1*F1_2*lambda;
    ddw(0,4) = F1_1*F2_2*lambda+F1_2*F2_1*mu;
    ddw(0,5) = F1_1*F3_2*lambda+F1_2*F3_1*mu;
    ddw(0,6) = mu*(F1_1*F1_3*2.0+F2_1*F2_3+F3_1*F3_3)+F1_1*F1_3*lambda;
    ddw(0,7) = F1_1*F2_3*lambda+F1_3*F2_1*mu;
    ddw(0,8) = F1_1*F3_3*lambda+F1_3*F3_1*mu;
    ddw(1,0) = mu*(F1_1*F2_1*2.0+F1_2*F2_2+F1_3*F2_3)+F1_1*F2_1*lambda;
    ddw(1,1) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F2_1*F2_1)*lambda+mu*(F1_1*F1_1+(F2_1*F2_1)*3.0+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1-1.0);
    ddw(1,2) = mu*(F2_1*F3_1*2.0+F2_2*F3_2+F2_3*F3_3)+F2_1*F3_1*lambda;
    ddw(1,3) = F1_2*F2_1*lambda+F1_1*F2_2*mu;
    ddw(1,4) = mu*(F1_1*F1_2+F2_1*F2_2*2.0+F3_1*F3_2)+F2_1*F2_2*lambda;
    ddw(1,5) = F2_1*F3_2*lambda+F2_2*F3_1*mu;
    ddw(1,6) = F1_3*F2_1*lambda+F1_1*F2_3*mu;
    ddw(1,7) = mu*(F1_1*F1_3+F2_1*F2_3*2.0+F3_1*F3_3)+F2_1*F2_3*lambda;
    ddw(1,8) = F2_1*F3_3*lambda+F2_3*F3_1*mu;
    ddw(2,0) = mu*(F1_1*F3_1*2.0+F1_2*F3_2+F1_3*F3_3)+F1_1*F3_1*lambda;
    ddw(2,1) = mu*(F2_1*F3_1*2.0+F2_2*F3_2+F2_3*F3_3)+F2_1*F3_1*lambda;
    ddw(2,2) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F3_1*F3_1)*lambda+mu*(F1_1*F1_1+F2_1*F2_1+(F3_1*F3_1)*3.0+F3_2*F3_2+F3_3*F3_3-1.0);
    ddw(2,3) = F1_2*F3_1*lambda+F1_1*F3_2*mu;
    ddw(2,4) = F2_2*F3_1*lambda+F2_1*F3_2*mu;
    ddw(2,5) = mu*(F1_1*F1_2+F2_1*F2_2+F3_1*F3_2*2.0)+F3_1*F3_2*lambda;
    ddw(2,6) = F1_3*F3_1*lambda+F1_1*F3_3*mu;
    ddw(2,7) = F2_3*F3_1*lambda+F2_1*F3_3*mu;
    ddw(2,8) = mu*(F1_1*F1_3+F2_1*F2_3+F3_1*F3_3*2.0)+F3_1*F3_3*lambda;
    ddw(3,0) = mu*(F1_1*F1_2*2.0+F2_1*F2_2+F3_1*F3_2)+F1_1*F1_2*lambda;
    ddw(3,1) = F1_2*F2_1*lambda+F1_1*F2_2*mu;
    ddw(3,2) = F1_2*F3_1*lambda+F1_1*F3_2*mu;
    ddw(3,3) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F1_2*F1_2)*lambda+mu*(F1_1*F1_1+(F1_2*F1_2)*3.0+F1_3*F1_3+F2_2*F2_2+F3_2*F3_2-1.0);
    ddw(3,4) = mu*(F1_1*F2_1+F1_2*F2_2*2.0+F1_3*F2_3)+F1_2*F2_2*lambda;
    ddw(3,5) = mu*(F1_1*F3_1+F1_2*F3_2*2.0+F1_3*F3_3)+F1_2*F3_2*lambda;
    ddw(3,6) = mu*(F1_2*F1_3*2.0+F2_2*F2_3+F3_2*F3_3)+F1_2*F1_3*lambda;
    ddw(3,7) = F1_2*F2_3*lambda+F1_3*F2_2*mu;
    ddw(3,8) = F1_2*F3_3*lambda+F1_3*F3_2*mu;
    ddw(4,0) = F1_1*F2_2*lambda+F1_2*F2_1*mu;
    ddw(4,1) = mu*(F1_1*F1_2+F2_1*F2_2*2.0+F3_1*F3_2)+F2_1*F2_2*lambda;
    ddw(4,2) = F2_2*F3_1*lambda+F2_1*F3_2*mu;
    ddw(4,3) = mu*(F1_1*F2_1+F1_2*F2_2*2.0+F1_3*F2_3)+F1_2*F2_2*lambda;
    ddw(4,4) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F2_2*F2_2)*lambda+mu*(F1_2*F1_2+F2_1*F2_1+(F2_2*F2_2)*3.0+F2_3*F2_3+F3_2*F3_2-1.0);
    ddw(4,5) = mu*(F2_1*F3_1+F2_2*F3_2*2.0+F2_3*F3_3)+F2_2*F3_2*lambda;
    ddw(4,6) = F1_3*F2_2*lambda+F1_2*F2_3*mu;
    ddw(4,7) = mu*(F1_2*F1_3+F2_2*F2_3*2.0+F3_2*F3_3)+F2_2*F2_3*lambda;
    ddw(4,8) = F2_2*F3_3*lambda+F2_3*F3_2*mu;
    ddw(5,0) = F1_1*F3_2*lambda+F1_2*F3_1*mu;
    ddw(5,1) = F2_1*F3_2*lambda+F2_2*F3_1*mu;
    ddw(5,2) = mu*(F1_1*F1_2+F2_1*F2_2+F3_1*F3_2*2.0)+F3_1*F3_2*lambda;
    ddw(5,3) = mu*(F1_1*F3_1+F1_2*F3_2*2.0+F1_3*F3_3)+F1_2*F3_2*lambda;
    ddw(5,4) = mu*(F2_1*F3_1+F2_2*F3_2*2.0+F2_3*F3_3)+F2_2*F3_2*lambda;
    ddw(5,5) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F3_2*F3_2)*lambda+mu*(F1_2*F1_2+F2_2*F2_2+F3_1*F3_1+(F3_2*F3_2)*3.0+F3_3*F3_3-1.0);
    ddw(5,6) = F1_3*F3_2*lambda+F1_2*F3_3*mu;
    ddw(5,7) = F2_3*F3_2*lambda+F2_2*F3_3*mu;
    ddw(5,8) = mu*(F1_2*F1_3+F2_2*F2_3+F3_2*F3_3*2.0)+F3_2*F3_3*lambda;
    ddw(6,0) = mu*(F1_1*F1_3*2.0+F2_1*F2_3+F3_1*F3_3)+F1_1*F1_3*lambda;
    ddw(6,1) = F1_3*F2_1*lambda+F1_1*F2_3*mu;
    ddw(6,2) = F1_3*F3_1*lambda+F1_1*F3_3*mu;
    ddw(6,3) = mu*(F1_2*F1_3*2.0+F2_2*F2_3+F3_2*F3_3)+F1_2*F1_3*lambda;
    ddw(6,4) = F1_3*F2_2*lambda+F1_2*F2_3*mu;
    ddw(6,5) = F1_3*F3_2*lambda+F1_2*F3_3*mu;
    ddw(6,6) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F1_3*F1_3)*lambda+mu*(F1_1*F1_1+F1_2*F1_2+(F1_3*F1_3)*3.0+F2_3*F2_3+F3_3*F3_3-1.0);
    ddw(6,7) = mu*(F1_1*F2_1+F1_2*F2_2+F1_3*F2_3*2.0)+F1_3*F2_3*lambda;
    ddw(6,8) = mu*(F1_1*F3_1+F1_2*F3_2+F1_3*F3_3*2.0)+F1_3*F3_3*lambda;
    ddw(7,0) = F1_1*F2_3*lambda+F1_3*F2_1*mu;
    ddw(7,1) = mu*(F1_1*F1_3+F2_1*F2_3*2.0+F3_1*F3_3)+F2_1*F2_3*lambda;
    ddw(7,2) = F2_3*F3_1*lambda+F2_1*F3_3*mu;
    ddw(7,3) = F1_2*F2_3*lambda+F1_3*F2_2*mu;
    ddw(7,4) = mu*(F1_2*F1_3+F2_2*F2_3*2.0+F3_2*F3_3)+F2_2*F2_3*lambda;
    ddw(7,5) = F2_3*F3_2*lambda+F2_2*F3_3*mu;
    ddw(7,6) = mu*(F1_1*F2_1+F1_2*F2_2+F1_3*F2_3*2.0)+F1_3*F2_3*lambda;
    ddw(7,7) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F2_3*F2_3)*lambda+mu*(F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+(F2_3*F2_3)*3.0+F3_3*F3_3-1.0);
    ddw(7,8) = mu*(F2_1*F3_1+F2_2*F3_2+F2_3*F3_3*2.0)+F2_3*F3_3*lambda;
    ddw(8,0) = F1_1*F3_3*lambda+F1_3*F3_1*mu;
    ddw(8,1) = F2_1*F3_3*lambda+F2_3*F3_1*mu;
    ddw(8,2) = mu*(F1_1*F1_3+F2_1*F2_3+F3_1*F3_3*2.0)+F3_1*F3_3*lambda;
    ddw(8,3) = F1_2*F3_3*lambda+F1_3*F3_2*mu;
    ddw(8,4) = F2_2*F3_3*lambda+F2_3*F3_2*mu;
    ddw(8,5) = mu*(F1_2*F1_3+F2_2*F2_3+F3_2*F3_3*2.0)+F3_2*F3_3*lambda;
    ddw(8,6) = mu*(F1_1*F3_1+F1_2*F3_2+F1_3*F3_3*2.0)+F1_3*F3_3*lambda;
    ddw(8,7) = mu*(F2_1*F3_1+F2_2*F3_2+F2_3*F3_3*2.0)+F2_3*F3_3*lambda;
    ddw(8,8) = lambda*((F1_1*F1_1)/2.0+(F1_2*F1_2)/2.0+(F1_3*F1_3)/2.0+(F2_1*F2_1)/2.0+(F2_2*F2_2)/2.0+(F2_3*F2_3)/2.0+(F3_1*F3_1)/2.0+(F3_2*F3_2)/2.0+(F3_3*F3_3)/2.0-3.0/2.0)+(F3_3*F3_3)*lambda+mu*(F1_3*F1_3+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+(F3_3*F3_3)*3.0-1.0);
}