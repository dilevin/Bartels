//collection of finite differencing routines to make life easier
#ifndef SIM_FINITE_DIFFERENCES_H
#define SIM_FINITE_DIFFERENCES_H

#include <Eigen/Dense>
#include <EigenTypes.h>
#include <BartelsTypes.h>

namespace sim {

    template<class Function, typename DerivedG, typename DerivedX, typename Scalar>
    void finite_differences_centered(Eigen::DenseBase<DerivedG> &grad, Function &f, const Eigen::DenseBase<DerivedX>  &x, Scalar tol=1e-6);
    
    template<class Function, typename DerivedH, typename DerivedX, typename Scalar>
    void finite_differences_hessian_centered(Eigen::DenseBase<DerivedH> &H, Function &f, const Eigen::DenseBase<DerivedX> &x, Scalar tol=1e-6);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/finite_differences.cpp>
#endif

#endif