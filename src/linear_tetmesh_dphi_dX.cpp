#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_dphi_dX.h>
#endif

template<typename DerivedRet, typename DerivedV>
void sim::linear_tetmesh_dphi_dX(Eigen::MatrixXx<DerivedRet> &dX, const Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E) {

    //dX.resize(E.rows(), 12); //store dphi_dX flattend out 

    Eigen::MatrixXx<DerivedRet> X; //I never access this for constant strain elements

    X.resize(E.rows(),3);
    auto dx = [](auto &a, auto &b, auto c, auto &d) { sim::linear_tet_dphi_dX(a, b, c, d); };
                    
    sim::eval_at_point(dX, V, E, dx, Eigen::Matrix43x<DerivedRet>(), X);


}