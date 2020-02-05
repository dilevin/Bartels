#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tet_neohookean_dq.h>
#endif

template<typename GradientType, typename DefoType, typename DerivedV, typename  Scalar>
void sim::linear_tet_neohookean_dq2(Eigen::DenseBase<GradientType> &g, const Eigen::MatrixBase<DerivedV> &q, Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, Scalar C, Scalar D, Scalar volume) {

    //get dpsi/dF2
    Eigen::Matrix9x<typename DerivedV::Scalar> dF; 
    Eigen::Matrix<typename DefoType::Scalar, 9,12> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,4> >(dXinv);

    //local positions
    Eigen::Vector12x<Scalar> qe;
    qe << q.segment(3*element(0),3), q.segment(3*element(1),3), q.segment(3*element(2),3), q.segment(3*element(3),3);

    //grab per element positions
    dpsi_neohookean_dF(dF, unflatten<3,3>((B*qe).eval()), C, D);

    g= B.transpose()*dF*volume;

}
