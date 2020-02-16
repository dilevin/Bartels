#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2d_linear_elasticity_dq2.h>
#endif

template<typename HessianType, typename DefoType, typename DerivedV, typename  Scalar>
void sim::linear_tri2d_linear_elasticity_dq2(Eigen::DenseBase<HessianType> &H, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, Scalar E, Scalar mu, Scalar volume) {


    Eigen::Matrix3x<typename DerivedV::Scalar> F = Eigen::Matrix3x<typename DerivedV::Scalar>::Zero();
    Eigen::Matrix6x<typename DerivedV::Scalar> dF2; 
    Eigen::Matrix<typename DerivedV::Scalar, 9,6> P;
    Eigen::Matrix<typename DerivedV::Scalar, 6,9> P2; //collect up off diagonal shears to reduce from 6 to 9
    
    P<<1, 0, 0, 0, 0, 0,
       0, 1, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0,
       0, 0, 1, 0, 0, 0,
       0, 0, 0, 1, 0, 0,
       0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 1, 0,
       0, 0, 0, 0, 0, 1,
       0, 0, 0, 0, 0, 0;

   P2<<1, 0, 0, 0, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 1, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 0, 0, 0, 1,
       0, 1, 0, 1, 0, 0, 0, 0, 0,
       0, 0, 0, 0, 0, 1, 0, 1, 0,
       0, 0, 1, 0, 0, 0, 1, 0, 0;

    F.block(0,0,3,2) = dXinv; 

    Eigen::Matrix<typename DefoType::Scalar, 6,6> B = P2*sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,3> >(F)*P;

    //local positions
    Eigen::Vector6x<Scalar> qe;
    qe << q.segment(2*element(0),2), q.segment(2*element(1),2), q.segment(2*element(2),2);

    //grab per element positions
    d2psi_linear_elasticity_de2(dF2, E, mu);

    H = B.transpose()*dF2*B*volume;

}
