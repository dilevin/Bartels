#ifndef SIM_LINESEARCH_BACKTRACKING_BISECTION_H
#define SIM_LINESEARCH_BACKTRACKING_BISECTION_H

#include <BartelsTypes.h>
#include <EigenTypes.h>

//Implementation of simple backtracking linesearch using bisection 
//Input:
//  x - initial point
//  d -  search direction
//  f - the optimization objective function f(x)
//  g - gradient of function at initial point
//  max_iterations - max line search iterations
//  alpha - max proportion of line search
//  c- sufficient decrease parameter
//  p - bisection ratio
//  Callback - callback that executes each line search iteration
//Output:
//  x - contains point to which linesearch converged, or final accepted point before termination
//  SolverExitStatus - exit code for solver 
namespace sim {
    
    template <typename DerivedX, typename Scalar, class Objective, class Callback = decltype(default_linesearch_callback)>
    SolverExitStatus linesearch_backtracking_bisection(
            Eigen::MatrixBase<DerivedX> &x, 
            Eigen::MatrixBase<DerivedX> &d,
            const Objective &f,
            Eigen::MatrixBase<DerivedX> &g,
            unsigned int max_iterations,
            Scalar alpha,
            Scalar c,
            Scalar p,
            const Callback func = default_linesearch_callback);
}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linesearch_backtracking_bisection.cpp>
#endif

#endif