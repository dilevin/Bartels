#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_F.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedDPhi>
void sim::linear_tetmesh_F(Eigen::DenseBase<DerivedRet> &F, Eigen::Ref<const Eigen::MatrixXi> E, const Eigen::MatrixBase<DerivedV> &q, const Eigen::DenseBase<DerivedDPhi> &dphidX)
{

    // finish this later
}

