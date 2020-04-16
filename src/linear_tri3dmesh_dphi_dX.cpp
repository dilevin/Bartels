#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri3dmesh_dphi_dX.h>
#endif

template<typename DerivedRet, typename DerivedV>
void sim::linear_tri3dmesh_dphi_dX(Eigen::MatrixXx<DerivedRet> &dX, const Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E) {

    Eigen::MatrixXx<DerivedRet> X; //I never access this for constant strain elements

    X.resize(E.rows(),3);
    auto dx = [](auto &a, auto &b, auto c, auto &d) { sim::linear_tri3d_dphi_dX(a, b, c, d); };
                    
    sim::eval_at_point(dX, V, E, dx, Eigen::Matrix3x<DerivedRet>(), X);


}