//collection of finite differencing routines to make life easier
#ifndef SIM_FINITE_DIFFERENCES_H
#define SIM_FINITE_DIFFERENCES_H

#include <Eigen/Dense>
#include <EigenTypes.h>
#include <BartelsTypes.h>

namespace sim {

    template<class Function, typename DerivedG, typename DerivedX, typename Scalar=double>
    void finite_differences_centered(Eigen::MatrixBase<DerivedG> &grad, Function &f, const Eigen::MatrixBase<DerivedX>  &x, Scalar tol=1e-6);
    
    template<class Function, typename DerivedH, typename DerivedX, typename Scalar=double>
    void finite_differences_hessian_centered(Eigen::MatrixBase<DerivedH> &H, Function &f, const Eigen::MatrixBase<DerivedX> &x, Scalar tol=1e-6);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/finite_differences.cpp>
#endif

#endif
