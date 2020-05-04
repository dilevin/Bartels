#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tet_stvk_dq.h>
#endif

template<typename HessianType, typename DefoType, typename DerivedV, typename Scalar, typename DerivedParams>
void sim::linear_tet_stvk_dq(Eigen::DenseBase<HessianType> &out, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedParams> &params, const Scalar &volume) {

    Eigen::Vector12x<Scalar> qe; qe << q.segment(3*element(0),3), q.segment(3*element(1),3), q.segment(3*element(2),3), q.segment(3*element(3),3); //qe
    Eigen::Matrix<typename DefoType::Scalar, 9,12> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,4> >(dphidX); //compute B

    Eigen::Vector9x<Scalar> dF; //type of dF

    dpsi_stvk_dF(dF, unflatten<3,3>((B*qe).eval()), params);

    out = B.transpose()*dF*volume;

}
