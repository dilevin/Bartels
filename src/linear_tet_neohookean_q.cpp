#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tet_neohookean_q.h>
#endif

template<typename DefoType, typename DerivedV, typename  ParamType, typename Scalar>
auto sim::linear_tet_neohookean_q(const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<ParamType> &params, Scalar volume) {

    Eigen::Matrix<typename DefoType::Scalar, 9,12> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,4> >(dXinv);

    //local positions
    Eigen::Vector12x<Scalar> qe;
    qe << q.segment(3*element(0),3), q.segment(3*element(1),3), q.segment(3*element(2),3), q.segment(3*element(3),3);

    //compute neohookean energy 
    return psi_neohookean_F(unflatten<3,3>((B*qe).eval()), params)*volume;

}
