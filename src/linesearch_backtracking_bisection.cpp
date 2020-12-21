#ifdef SIM_STATIC_LIBRARY
# include<../include/linesearch_backtracking_bisection.h>
#endif

template <typename DerivedX, typename Scalar, class Objective, class Callback>
sim::SolverExitStatus sim::linesearch_backtracking_bisection(Eigen::MatrixBase<DerivedX> &x, 
                            Eigen::MatrixBase<DerivedX> &d, 
                            const Objective &f,
                            Eigen::MatrixBase<DerivedX> &g,
                            unsigned int max_iterations,
                            Scalar alpha,
                            Scalar c,
                            Scalar p,
                            const Callback func) {


    unsigned int iteration_count = 0;

    Scalar f0 = f(x);
    
    while((f(x+alpha*d) > f(x) + c*g.transpose()*d) && iteration_count < max_iterations) {

        alpha  *= p; 
        iteration_count++;
        func(x);
    }

    x += alpha*d;
    
    return (iteration_count == max_iterations ? SolverExitStatus::MAX_ITERATIONS_REACHED : SolverExitStatus::CONVERGED);
}