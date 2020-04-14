#ifdef SIM_STATIC_LIBRARY
# include<../include/dpsi_neohookean_dF.h>
#endif

template<typename GradientType, typename DefoType, typename ParameterType>
void sim::dpsi_neohookean_dF(Eigen::MatrixBase<GradientType> &dw, const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params) {

    /*typename DefoType::Scalar f11, f12, f13, f21, f22, f23, f31, f32, f33;
    
    typename DefoType::Scalar C = params(0);
    typename DefoType::Scalar D = params(1);


    f11 = F(0,0);
    f12 = F(0,1);
    f13 = F(0,2);
    f21 = F(1,0);
    f22 = F(1,1);
    f23 = F(1,2);
    f31 = F(2,0);
    f32 = F(2,1);
    f33 = F(2,2);

    dw[0] = 2*D*(f23*f32 - f22*f33)*(1 + f13*f22*f31 - f12*f23*f31 - f13*f21*f32 + f11*f23*f32 + f12*f21*f33 - f11*f22*f33) + (2*C*(3*f11*(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f12*f21*f33) + std::pow(f11,2)*(-2*f23*f32 + 2*f22*f33) + (f23*f32 - f22*f33)*(std::pow(f12,2) + std::pow(f13,2) + std::pow(f21,2) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2) + std::pow(f33,2))))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
        
    dw[1] = 2*D*(f23*f31 - f21*f33)*(-1 - f13*f22*f31 + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33) - (2*C*(std::pow(f12,2)*(-2*f23*f31 + 2*f21*f33) + 3*f12*(f13*f22*f31 - f13*f21*f32 + f11*f23*f32 - f11*f22*f33) + (f23*f31 - f21*f33)*(std::pow(f11,2) + std::pow(f13,2) + std::pow(f21,2) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2) + std::pow(f33,2))))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
        
    dw[2] = 2*D*(f22*f31 - f21*f32)*(1 + f13*f22*f31 - f12*f23*f31 - f13*f21*f32 + f11*f23*f32 + f12*f21*f33 - f11*f22*f33) + (2*C*f13)/stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,2.0) + (2*C*(f22*f31 - f21*f32)*(std::pow(f11,2) + std::pow(f12,2) + std::pow(f13,2) + std::pow(f21,2) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2) + std::pow(f33,2)))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
        
    dw[3] = 2*D*(f13*f32 - f12*f33)*(-1 - f13*f22*f31 + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33) + (2*C*f21)/stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,2.0) - (2*C*(f13*f32 - f12*f33)*(std::pow(f11,2) + std::pow(f12,2) + std::pow(f13,2) + std::pow(f21,2) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2) + std::pow(f33,2)))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
        
    dw[4] = 2*D*(f13*f31 - f11*f33)*(1 + f13*f22*f31 - f12*f23*f31 - f13*f21*f32 + f11*f23*f32 + f12*f21*f33 - f11*f22*f33) + (2*C*f22)/stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,2.0) + (2*C*(f13*f31 - f11*f33)*(std::pow(f11,2) + std::pow(f12,2) + std::pow(f13,2) + std::pow(f21,2) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2) + std::pow(f33,2)))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
        
    dw[5] = 2*D*(f12*f31 - f11*f32)*(-1 - f13*f22*f31 + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33) + (2*C*f23)/stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,2.0) - (2*C*(f12*f31 - f11*f32)*(std::pow(f11,2) + std::pow(f12,2) + std::pow(f13,2) + std::pow(f21,2) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2) + std::pow(f33,2)))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
        
    dw[6] = 2*D*(f13*f22 - f12*f23)*(1 + f13*f22*f31 - f12*f23*f31 - f13*f21*f32 + f11*f23*f32 + f12*f21*f33 - f11*f22*f33) + (2*C*f31)/stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,2.0) + (2*C*(f13*f22 - f12*f23)*(std::pow(f11,2) + std::pow(f12,2) + std::pow(f13,2) + std::pow(f21,2.0) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2) + std::pow(f33,2)))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
        
    dw[7] = 2*D*(f13*f21 - f11*f23)*(-1 - f13*f22*f31 + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33) + (2*C*f32)/stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,2.0) - (2*C*(f13*f21 - f11*f23)*(std::pow(f11,2) + std::pow(f12,2) + std::pow(f13,2) + std::pow(f21,2) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2) + std::pow(f33,2)))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
        
    dw[8] = 2*D*(f12*f21 - f11*f22)*(1 + f13*f22*f31 - f12*f23*f31 - f13*f21*f32 + f11*f23*f32 + f12*f21*f33 - f11*f22*f33) - (2*C*((-(f12*f21) + f11*f22)*(std::pow(f11,2) + std::pow(f12,2) + std::pow(f13,2) + std::pow(f21,2) + std::pow(f22,2) + std::pow(f23,2) + std::pow(f31,2) + std::pow(f32,2)) + 3*(f13*f22*f31 - f12*f23*f31 - f13*f21*f32 + f11*f23*f32)*f33 + 2*(f12*f21 - f11*f22)*std::pow(f33,2)))/(3.*stablePow(-(f13*f22*f31) + f12*f23*f31 + f13*f21*f32 - f11*f23*f32 - f12*f21*f33 + f11*f22*f33,5.0));
    */

        typename DefoType::Scalar F1_1, F1_2, F1_3, F2_1, F2_2, F2_3,F3_1, F3_2, F3_3;
    
        typename DefoType::Scalar params1 = params(0);
        typename DefoType::Scalar params2 = params(1);

        F1_1 = F(0,0);
        F1_2 = F(0,1);
        F1_3 = F(0,2);
        F2_1 = F(1,0);
        F2_2 = F(1,1);
        F2_3 = F(1,2);
        F3_1 = F(2,0);
        F3_2 = F(2,1);
        F3_3 = F(2,2);

       dw[0] = params1*(F1_1*2.0-((F2_2*F3_3-F2_3*F3_2)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))-params2*(F2_2*F3_3-F2_3*F3_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;
       dw[1] = params1*(F2_1*2.0+((F1_2*F3_3-F1_3*F3_2)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))+params2*(F1_2*F3_3-F1_3*F3_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;
       dw[2] = params1*(F3_1*2.0-((F1_2*F2_3-F1_3*F2_2)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))-params2*(F1_2*F2_3-F1_3*F2_2)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;
       dw[3] = params1*(F1_2*2.0+((F2_1*F3_3-F2_3*F3_1)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))+params2*(F2_1*F3_3-F2_3*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;
       dw[4] = params1*(F2_2*2.0-((F1_1*F3_3-F1_3*F3_1)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))-params2*(F1_1*F3_3-F1_3*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;
       dw[5] = params1*(F3_2*2.0+((F1_1*F2_3-F1_3*F2_1)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))+params2*(F1_1*F2_3-F1_3*F2_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;
       dw[6] = params1*(F1_3*2.0-((F2_1*F3_2-F2_2*F3_1)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))-params2*(F2_1*F3_2-F2_2*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;
       dw[7] = params1*(F2_3*2.0+((F1_1*F3_2-F1_2*F3_1)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))+params2*(F1_1*F3_2-F1_2*F3_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;
       dw[8] = params1*(F3_3*2.0-((F1_1*F2_2-F1_2*F2_1)*2.0)/(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1))-params2*(F1_1*F2_2-F1_2*F2_1)*(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0)*2.0;



}