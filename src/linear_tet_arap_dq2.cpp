#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tet_arap_dq2.h>
#endif

template<typename HessianType, typename DefoType, typename DerivedV, typename Scalar, typename DerivedParams>
void sim::linear_tet_arap_dq2(Eigen::DenseBase<HessianType> &out, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedParams> &params, const Scalar &volume) {

    Eigen::Vector12x<Scalar> qe; qe << q.segment(3*element(0),3), q.segment(3*element(1),3), q.segment(3*element(2),3), q.segment(3*element(3),3); //qe
    Eigen::Matrix<typename DefoType::Scalar, 9,12> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,4> >(dphidX); //compute B

    Eigen::Matrix9x<Scalar> dF; //type of dF

    d2psi_stretch_dF2(dF, unflatten<3,3>((B*qe).eval()), [](auto &a, auto &b, auto &c) { sim::dpsi_arap_dS(a,b,c); }, [](auto &a, auto &b, auto &c) { sim::d2psi_arap_dS2(a,b,c); },  params);

    out = B.transpose()*dF*B*volume;

}
