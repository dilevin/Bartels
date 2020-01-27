#ifndef SIM_QUADRATURE_RULE_H
#define SIM_QUADRATURE_RULE_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

#include <iostream>

namespace sim {

    template<typename PointsType, typename WeightsType>
    void quadrature_single_point(Eigen::DenseBase<PointsType> &quadrature_points, 
                                 Eigen::DenseBase<WeightsType> &quadrature_weights, 
                                 Eigen::Ref<const Eigen::MatrixXi> elements);

}

#ifndef SIM_STATIC_LIBRARY
# include<../src/flatten_multiply.cpp>
#endif

#endif