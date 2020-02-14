#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2d_neohookean_dq2.h>
#endif

template<typename HessianType, typename DefoType, typename DerivedV, typename  Scalar>
void sim::linear_tri2d_neohookean_dq2(Eigen::DenseBase<HessianType> &H, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, Scalar C, Scalar D, Scalar volume) {


    Eigen::Matrix3x<typename DerivedV::Scalar> F = Eigen::Matrix3x<typename DerivedV::Scalar>::Zero();
    Eigen::Matrix9x<typename DerivedV::Scalar> dF2; 
    Eigen::Matrix<typename DerivedV::Scalar, 9,6> P;
    Eigen::Vector9x<typename DerivedV::Scalar> one = Eigen::Vector9x<typename DerivedV::Scalar>::Zero();

    one(8) = 1.0;

    P<<1, 0, 0, 0, 0, 0,
       0, 1, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0,
       0, 0, 1, 0, 0, 0,
       0, 0, 0, 1, 0, 0,
       0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 1, 0,
       0, 0, 0, 0, 0, 1,
       0, 0, 0, 0, 0, 0;

    F.block(0,0,3,2) = dXinv; 

    Eigen::Matrix<typename DefoType::Scalar, 9,6> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,3> >(F)*P;

    //local positions
    Eigen::Vector6x<Scalar> qe;
    qe << q.segment(2*element(0),2), q.segment(2*element(1),2), q.segment(2*element(2),2);

    //grab per element positions
    d2psi_neohookean_dF2(dF2, unflatten<3,3>((B*qe+one).eval()), C, D);

    H = B.transpose()*dF2*B*volume;

}
