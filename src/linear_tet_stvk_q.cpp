#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tet_stvk_q.h>
#endif

template<typename DefoType, typename DerivedV, typename Scalar, typename DerivedParams>
auto sim::linear_tet_stvk_q(const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dphidX, const Eigen::MatrixBase<DerivedParams> &params, const Scalar &volume) {

    Eigen::Vector12x<Scalar> qe; qe << q.segment(3*element(0),3), q.segment(3*element(1),3), q.segment(3*element(2),3), q.segment(3*element(3),3); //qe
    Eigen::Matrix<typename DefoType::Scalar, 9,12> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,4> >(dphidX); //compute B

    return psi_stvk_F(unflatten<3,3>((B*qe).eval()), params)*volume;

}
