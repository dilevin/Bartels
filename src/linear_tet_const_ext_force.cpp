#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tet_const_ext_force.h>
#endif

template<typename VectorType, typename TractionType, typename ScalarType>
void sim::linear_tet_const_ext_force(Eigen::DenseBase<VectorType> &f, Eigen::Ref<const Eigen::RowVectorXi> element, const ScalarType volume, const Eigen::DenseBase<TractionType> &traction) {

    f = traction.replicate(4,1);
    f *= (0.25*volume);
}
