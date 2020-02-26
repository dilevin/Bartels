#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tet_linear_elasticity_dq.h>
#endif

template<typename HessianType, typename DefoType, typename DerivedV, typename Scalar, typename DerivedParams>
void sim::linear_tet_linear_elasticity_dq(Eigen::DenseBase<HessianType> &out, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedParams> &params, const Scalar &volume) {

    Eigen::Vector12x<Scalar> qe; qe << q.segment(3*element(0),3), q.segment(3*element(1),3), q.segment(3*element(2),3), q.segment(3*element(3),3); //qe
    
    Eigen::Vector9x<Scalar> dF; //type of dF
    Eigen::Matrix<typename DefoType::Scalar, 6,9> P2;
    
    P2<<1, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 1, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 1,
       0, 0, 0, 0, 0, 1, 0, 1, 0,
       0, 0, 1, 0, 0, 0, 1, 0, 0,
       0, 1, 0, 1, 0, 0, 0, 0, 0;

    Eigen::Matrix<typename DefoType::Scalar, 9,12> B = P2*sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,4> >(dXinv); //compute B

    Eigen::Matrix6x<typename DefoType::Scalar> e = 0.5*(unflatten<3,3>((B*qe) + unflatten<3,3>((B*qe).transpose());
    Eigen::Vector6x<ypename DefoType::Scalar> e_vec;
    e_vec << e(0,0), e(1,1), e(2,2), 2.*e(1,2), 2.*e(0,2), 2.*e(0,1); 

    dpsi_linear_elasticity_de(dF, e_vec, params);

    out = B.transpose()*dF*volume;

}
