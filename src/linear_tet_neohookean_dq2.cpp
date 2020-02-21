#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tet_neohookean_dq2.h>
#endif

template<typename HessianType, typename DefoType, typename DerivedV, typename  ParamType, typename Scalar>
void sim::linear_tet_neohookean_dq2(Eigen::DenseBase<HessianType> &H, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<ParamType> &params, Scalar volume) {

    //get dpsi/dF2
    Eigen::Matrix9x<typename DerivedV::Scalar> dF2; 
    Eigen::Matrix<typename DefoType::Scalar, 9,12> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,4> >(dXinv);

    //local positions
    Eigen::Vector12x<Scalar> qe;
    qe << q.segment(3*element(0),3), q.segment(3*element(1),3), q.segment(3*element(2),3), q.segment(3*element(3),3);

    //grab per element positions
    d2psi_neohookean_dF2(dF2, unflatten<3,3>((B*qe).eval()), params);

    H = B.transpose()*dF2*B*volume;

}
