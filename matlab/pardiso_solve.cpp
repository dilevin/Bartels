#include <mex.h>

//matlab hooks from libigl (taken directly from gptoolbox)
#include <mex.h>
#include <igl/C_STR.h>
#include <igl/matlab/mexErrMsgTxt.h>
#undef assert
#define assert( isOK ) ( (isOK) ? (void)0 : (void) mexErrMsgTxt(C_STR(__FILE__<<":"<<__LINE__<<": failed assertion `"<<#isOK<<"'"<<std::endl) ) )

#include <igl/matlab/MexStream.h>
#include <igl/matlab/parse_rhs.h>
#include "utils/prepare_lhs_extra.h"
#include <igl/matlab/validate_arg.h>
#include <igl/list_to_matrix.h>
#include <igl/Timer.h>

//bartels
#include <PardisoOpenSource.h>

#ifdef BARTELS_USE_OPENMP
#include <omp.h>
#endif

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    /* variable declarations here */
    Eigen::SparseMatrix<double> A;
    Eigen::MatrixXd b;
    Eigen::MatrixXd x;

    igl::matlab::parse_rhs(prhs+0,A);
    igl::matlab::parse_rhs_double(prhs+1, b);
    
    #ifdef BARTELS_USE_PARDISO
        igl::Timer timer;
        //Eigen::PardisoLU<Eigen::SparseMatrix<double, Eigen::ColMajor>> test(4);
        Eigen::PardisoLDLT<Eigen::SparseMatrix<double, Eigen::ColMajor>> test(8);
        timer.start();
        test.compute(A);
        x = test.solve(b);
        timer.stop();
        mexPrintf("Time: %f\n", timer.getElapsedTimeInSec());

    #endif

    igl::matlab::prepare_lhs_double(x, plhs);
   
}