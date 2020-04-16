#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2d_dphi_dX.h>
#endif

template<typename DerivedP, typename DerivedV, typename DerivedR>
void sim::linear_tri2d_dphi_dX(Eigen::DenseBase<DerivedP> &dphi, const Eigen::MatrixBase<DerivedV> &V, 
                            Eigen::Ref<const Eigen::RowVectorXi> element, 
                            Eigen::MatrixBase<DerivedR> const & X) {

        Eigen::Matrix2d tmp;
        dphi.block(1,0,2,2) << (V.row(element(1)) - V.row(element(0))), (V.row(element(2)) - V.row(element(0)));

        dphi.block(1,0,2,2).transposeInPlace();
        inverse22(tmp, dphi.block(1,0,2,2));
        dphi.block(1,0,2,2) = tmp;
        dphi.block(0,0,1,2) = -dphi.block(1,0,2,2).colwise().sum(); 
                                
}