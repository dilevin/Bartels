#ifdef SIM_STATIC_LIBRARY
# include<../include/assemble.h>
#endif

template<typename PointsType, typename WeightsType>
void sim::quadrature_single_point(Eigen::DenseBase<PointsType> &quadrature_points, 
                             Eigen::DenseBase<WeightsType> &quadrature_weights, 
                             Eigen::Ref<const Eigen::MatrixXi> elements) {


    using WeightsScalar = typename WeightsType::Scalar;
    using PointsScalar = typename PointsType::Scalar;

    quadrature_weights.resize(elements.rows(), 1); //num elements x num quadrature points
    quadrature_points.resize(elements.rows(), 1); //num elements x num quadrature points 
    
    quadrature_weights.setConstant(static_cast<WeightsScalar>(1.));
    quadrature_points.setConstant(static_cast<PointsScalar>(1.0)/static_cast<PointsScalar>(3.0));

}