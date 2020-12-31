//collection of finite differencing routines to make life easier
#ifndef SIM_FINITE_DIFFERENCES_H
#define SIM_FINITE_DIFFERENCES_H

#include <Eigen/Dense>
#include <EigenTypes.h>
#include <BartelsTypes.h>

namespace sim {

template<class Function, typename Scalar,
         int GRowsAtCompileTime,
         int GColsAtCompileTime,
         int GOptions = 0,
         int GMaxRowsAtCompileTime = GRowsAtCompileTime,
         int GMaxColsAtCompileTime = GColsAtCompileTime,
         typename DerivedX>
    void finite_differences_centered(Eigen::Matrix<Scalar, GRowsAtCompileTime, GColsAtCompileTime, GOptions, GMaxRowsAtCompileTime, GMaxColsAtCompileTime> &grad, Function &f, const Eigen::MatrixBase<DerivedX>  &x, Scalar tol=1e-6);
    
template<class Function, typename Scalar,
         int HRowsAtCompileTime,
         int HColsAtCompileTime,
         int HOptions = 0,
         int HMaxRowsAtCompileTime = HRowsAtCompileTime,
         int HMaxColsAtCompileTime = HColsAtCompileTime,
         typename DerivedX>
    void finite_differences_hessian_centered(Eigen::Matrix<Scalar, HRowsAtCompileTime, HColsAtCompileTime, HOptions, HMaxRowsAtCompileTime, HMaxColsAtCompileTime> &H, Function &f, const Eigen::MatrixBase<DerivedX> &x, Scalar tol=1e-6);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/finite_differences.cpp>
#endif

#endif
