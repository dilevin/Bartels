#ifdef SIM_STATIC_LIBRARY
#include<../include/linear_tet_dphi_dX.h>
#endif

template<typename DerivedP, typename DerivedV, typename DerivedR>
void sim::linear_tet_dphi_dX(Eigen::DenseBase<DerivedP> &dphi, const  Eigen::MatrixBase<DerivedV> &V, 
                            Eigen::Ref<const Eigen::RowVectorXi> element, 
                            Eigen::MatrixBase<DerivedR> const & X) {

        Eigen::Matrix3d tmp;
        dphi.block(1,0,3,3) << (V.row(element(1)) - V.row(element(0))), (V.row(element(2)) - V.row(element(0))), (V.row(element(3)) - V.row(element(0)));

        dphi.block(1,0,3,3).transposeInPlace();
        inverse33(tmp, dphi.block(1,0,3,3));
        dphi.block(1,0,3,3) = tmp;
        dphi.block(0,0,1,3) = -dphi.block(1,0,3,3).colwise().sum(); 
                                
}