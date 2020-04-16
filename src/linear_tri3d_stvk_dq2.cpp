#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri3d_stvk_dq2.h>
#endif

//the normal and the normal derivive 
template<typename HessianType, typename DefoType, typename DerivedV,
         typename NormalType,
         typename DNormalType,
         typename Scalar, 
         typename DerivedParams>
void sim::linear_tri3d_stvk_dq2(Eigen::DenseBase<HessianType> &out, const Eigen::MatrixBase<DerivedV> &q, const Eigen::Ref<const Eigen::RowVectorXi> element,  
                                    const Eigen::MatrixBase<DefoType> &dXinv, 
                                    const Eigen::MatrixBase<NormalType> &N,
                                    const Eigen::MatrixBase<NormalType> &n,
                                    const Eigen::MatrixBase<DNormalType> &dndq,
                                    const Eigen::MatrixBase<DerivedParams> &params, const Scalar &volume) {


    //qe
    Eigen::Vector9x<Scalar> qe; qe << q.segment(3*element(0),3), q.segment(3*element(1),3), q.segment(3*element(2),3);

    //normal vector to fix up deformation gradient
    Eigen::Vector3x<typename NormalType::Scalar> na = n.transpose();
    Eigen::Matrix<typename NormalType::Scalar, 1,3> Na = N;
    Eigen::Vector9x<typename DefoType::Scalar> n_vec = sim::flatten(na*Na);

    Eigen::Matrix<typename DefoType::Scalar, 9,9> B = sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,3> >(dXinv);
    
    //normal component goes here
    B += sim::flatten_multiply_right<Eigen::Matrix<typename DefoType::Scalar, 3,1> >(Na)*sim::unflatten<3,9>(dndq);

    //for now ignore second derivative for deformation gradient.

    Eigen::Matrix9x<Scalar> dF; //type of dF

    d2psi_stvk_dF2(dF, unflatten<3,3>((B*qe+n_vec).eval()), params);

    out = B.transpose()*dF*B*volume;

}
