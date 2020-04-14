#ifdef SIM_STATIC_LIBRARY
# include<../include/psi_neohookean_F.h>
#endif

template<typename DefoType, typename ParameterType>
typename DefoType::Scalar sim::psi_neohookean_F(const Eigen::MatrixBase<DefoType> &F, const Eigen::MatrixBase<ParameterType> &params) {

    // using Scalar = typename DefoType::Scalar;
    // Scalar detF = F.determinant();
    // Scalar J23 = stablePow(detF,2.0);
    // J23=1.0/J23;
    // Eigen::Matrix<Scalar, 3,3> Cbar = J23*F.transpose()*F;
    
    // return params(0)*(Cbar.trace() - 3.0) + params(1)*(detF - 1)*(detF - 1);

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

    return params1*(log(F1_1*F2_2*F3_3-F1_1*F2_3*F3_2-F1_2*F2_1*F3_3+F1_2*F2_3*F3_1+F1_3*F2_1*F3_2-F1_3*F2_2*F3_1)*-2.0+F1_1*F1_1+F1_2*F1_2+F1_3*F1_3+F2_1*F2_1+F2_2*F2_2+F2_3*F2_3+F3_1*F3_1+F3_2*F3_2+F3_3*F3_3-3.0)+params2*pow(-F1_1*F2_2*F3_3+F1_1*F2_3*F3_2+F1_2*F2_1*F3_3-F1_2*F2_3*F3_1-F1_3*F2_1*F3_2+F1_3*F2_2*F3_1+1.0,2.0);
}

