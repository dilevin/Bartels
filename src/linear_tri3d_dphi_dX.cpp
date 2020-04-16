#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri3d_dphi_dX.h>
#endif

//dphi is 3x3 
template<typename DerivedP, typename DerivedV, typename DerivedR>
void sim::linear_tri3d_dphi_dX(Eigen::DenseBase<DerivedP> &dphi, const Eigen::MatrixBase<DerivedV> &V, 
                            Eigen::Ref<const Eigen::RowVectorXi> element, 
                            Eigen::MatrixBase<DerivedR> const & X) {

        Eigen::Matrix<typename DerivedP::Scalar,3,2> T; 
        
        T.col(0) = (V.row(element(1)) - V.row(element(0))).transpose();
        T.col(1) = (V.row(element(2)) - V.row(element(0))).transpose();

        dphi.block(1,0, 2,3) = (T.transpose()*T).inverse()*T.transpose();
        dphi.row(0) = -dphi.block(1,0, 2,3).colwise().sum();                                
}