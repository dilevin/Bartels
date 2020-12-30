#ifndef SIM_OPTIMIZATION_GRADIENT_BASED_H
#define SIM_OPTIMIZATION_GRADIENT_BASED_H

#include <BartelsTypes.h>
#include <EigenTypes.h>
#include <linesearch_backtracking_bisection.h>
#include <search_direction_newton_sparse.h>

//gradient-based optimization schemes
namespace sim {
    
    //1st-order
    //unconstrained gradient descent with simple bisection, backtracking
     
    //2nd-order
    //unconstrained newtons method with simple bisection, backtracking
    //x - initial guess for solver, contains final value on exit
    //f - f(x) returns the value for the energy at x
    //g - g(tmp_g, x)  returns the value of the gradient in tmp_g
    //H - H(tmp_H, x) returns the value of the hessian in tmp_H
    //Solver - linear solver to use for search direction calculation
    //tmp_g - work space for computing the gradient during newton's method
    //tmp_H - work space for computing the gradient during newton's method
    //tmp_d - work space for storing the search direction during newton's method
    //gradient_tol - consider converged if gradient is less than this tolerance
    //max_iterations - max number of newton iterations
    //max_iterations_ls - max number of line search iterations
    //alpha - initial percentage of step size for line search (default 1.0)
    //c - sufficient decrease toloerance (default 1e-8)
    //p -  
    //opt_call - opt_call(auto &x, auto &g, auto &H, SolverExitStatus &searchstatus) optimization callback function, default does nothing
    //ls_call -  ls_call(auto &x) line search callback function (default does nothing)
    template <typename DerivedX, class Energy, class Gradient, class Hessian, 
              typename DerivedG, typename DerivedH,
              typename Scalar, 
              class SparseLinearSolver=Eigen::SparseLU<Eigen::MatrixBase<DerivedH> > ,
              class OptimizationCallback = decltype(default_optimization_callback),
              class LineSearchCallback = decltype(default_linesearch_callback) >
    inline SolverExitStatus newtons_method_bisection(Eigen::MatrixBase<DerivedX> &x,
                                                 Energy &f, 
                                                 Gradient &g, 
                                                 Hessian &H, 
                                                 SparseLinearSolver &solver,
                                                 Eigen::MatrixBase<DerivedG> &tmp_g,
                                                 Eigen::MatrixBase<DerivedH> &tmp_H,
                                                 Eigen::MatrixBase<DerivedG> &tmp_d,
                                                 Scalar gradient_tol = 1e-3,
                                                 unsigned int max_iterations = 100,
                                                 unsigned int max_iterations_ls = 100,
                                                 Scalar alpha = 1.0,
                                                 Scalar c = 1e-8,
                                                 Scalar p = 0.5,
                                                 const OptimizationCallback opt_call = default_optimization_callback,
                                                 const LineSearchCallback ls_call = default_linesearch_callback) 
                                                 
    {
        unsigned int iteration_count = 0;

        if(tmp_g.rows() != x.rows()) {
            tmp_g.resize(x.rows(),1);
        }   

        //compute hessian
        if((tmp_H.rows() != x.rows()) || (tmp_H.cols() != x.rows()) ) {
            tmp_H.resize(x.rows(), x.rows()); 
        }

        do {

            //compute gradient
            g(tmp_g, x);

            //check for convergence and return if converged 
            if(tmp_g.transpose()*tmp_g < gradient_tol*gradient_tol) 
                return SolverExitStatus::CONVERGED;

            //compute search direction
            if(!search_direction_newton_sparse(tmp_d, tmp_g, tmp_H, solver))
            {
                std::cout<<"Computing search direction failed in newtons method \n";
                exit(1);
            }

            //line search 
            SolverExitStatus ls_status = linesearch_backtracking_bisection(x, tmp_d, f, tmp_g, 
                                                                           max_iterations_ls, 
                                                                           alpha, c, p,
                                                                           ls_call);

            opt_call(x, tmp_g, tmp_H, ls_status);

            iteration_count++;

        } while(iteration_count <= max_iterations);

        return SolverExitStatus::MAX_ITERATIONS_REACHED;
        
    }

    
}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/optimization_gradient_based.cpp>
#endif

#endif