#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2d_arap_q.h>
#endif

template<typename DefoType, typename DerivedV, typename Scalar, typename DerivedParams>
auto sim::linear_tri2d_arap_q(const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedParams> &params, const Scalar &volume) {

    Eigen::Vector6x<Scalar> qe; qe << q.segment(2*element(0),2), q.segment(2*element(1),2), q.segment(2*element(2),2); //qe
    Eigen::Matrix3x<typename DefoType::Scalar> F = Eigen::Matrix3x<typename DerivedV::Scalar>::Zero();  Eigen::Vector9x<typename DerivedV::Scalar> one = Eigen::Vector9x<typename DerivedV::Scalar>::Zero(); one(8) = 1.0; Eigen::Matrix<typename DerivedV::Scalar, 9,6> P; P<<1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0; F.block(0,0,3,2) = dphidX; Eigen::Matrix<typename DefoType::Scalar, 9,6> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,3> >(F)*P; //compute B

    return volume*psi_stretch_F(unflatten<3,3>((B*qe + one).eval()), [](auto &a, auto &b) { return sim::psi_arap_S(a,b); }, params);

}
