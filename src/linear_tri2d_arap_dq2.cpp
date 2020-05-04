#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2d_arap_dq2.h>
#endif

template<typename HessianType, typename DefoType, typename DerivedV, typename Scalar, typename DerivedParams>
void sim::linear_tri2d_arap_dq2(Eigen::DenseBase<HessianType> &out, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedParams> &params, const Scalar &volume) {

    Eigen::Vector6x<Scalar> qe; qe << q.segment(2*element(0),2), q.segment(2*element(1),2), q.segment(2*element(2),2); //qe
    Eigen::Matrix3x<typename DefoType::Scalar> F = Eigen::Matrix3x<typename DerivedV::Scalar>::Zero();  Eigen::Vector9x<typename DerivedV::Scalar> one = Eigen::Vector9x<typename DerivedV::Scalar>::Zero(); one(8) = 1.0; Eigen::Matrix<typename DerivedV::Scalar, 9,6> P; P<<1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0; F.block(0,0,3,2) = dphidX; Eigen::Matrix<typename DefoType::Scalar, 9,6> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,3> >(F)*P; //compute B

    Eigen::Matrix9x<Scalar> dF; //type of dF

    d2psi_stretch_dF2(dF, unflatten<3,3>((B*qe+one).eval()), [](auto &a, auto &b, auto &c) { sim::dpsi_arap_dS(a,b,c); }, [](auto &a, auto &b, auto &c) { sim::d2psi_arap_dS2(a,b,c); },  params);

    out = B.transpose()*dF*B*volume;

}
