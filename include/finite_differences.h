//collection of finite differencing routines to make life easier
#ifndef SIM_FINITE_DIFFERENCES_H
#define SIM_FINITE_DIFFERENCES_H

#include <Eigen/Dense>
#include <EigenTypes.h>
#include <BartelsTypes.h>

namespace sim {

    template<class Function, typename Scalar, int RowsAtCompileTime>
    void finite_differences_centered(Eigen::Matrix<Scalar, RowsAtCompileTime, 1> &grad, Function &f, const Eigen::Matrix<Scalar, RowsAtCompileTime, 1>  &x, Scalar tol=1e-6);
    
    template<class Function, typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
    void finite_differences_hessian_centered(Eigen::Matrix<Scalar, RowsAtCompileTime, ColsAtCompileTime> &H, Function &f, const Eigen::Matrix<Scalar, RowsAtCompileTime, 1> &x, Scalar tol=1e-6);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/finite_differences.cpp>
#endif

#endif