#ifndef SIM_EVAL_AT_POINT_H
#define SIM_EVAL_AT_POINT_H

#include <Eigen/Dense>
#include <EigenTypes.h>

#include <flatten.h>

namespace sim {

    template<typename DerivedRet, typename DerivedV,
             int Rows, int Cols, int Options, int MaxRows, int MaxCols,
            typename Func2, typename DerivedX>
    void eval_at_point(Eigen::MatrixXx<DerivedRet> &results, const Eigen::MatrixBase<DerivedV> &V, Eigen::Ref<const Eigen::MatrixXi> E, 
                       Func2 func, Eigen::Matrix<DerivedRet, Rows, Cols, Options, MaxRows, MaxCols> tmp, 
                       const Eigen::MatrixBase<DerivedX> &X);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/eval_at_point.cpp>
#endif

#endif
