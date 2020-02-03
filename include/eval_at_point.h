#ifndef SIM_EVAL_AT_POINT_H
#define SIM_EVAL_AT_POINT_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <flatten.h>

namespace sim {

    template<typename Scalar, int Rows, int Cols, typename Func2, typename DerivedV>
    void eval_at_point(Eigen::MatrixXd &results, const Eigen::MatrixXd &V, Eigen::Ref<const Eigen::MatrixXi> E, 
                       Func2 func, Eigen::Matrix<Scalar, Rows, Cols> tmp, const Eigen::MatrixBase<DerivedV> &X);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/eval_at_point.cpp>
#endif

#endif
