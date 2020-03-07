#include <mex.h>

//matlab hooks from libigl (taken directly from gptoolbox)
#include <mex.h>
#include <igl/C_STR.h>
#include <igl/matlab/mexErrMsgTxt.h>
#undef assert
#define assert( isOK ) ( (isOK) ? (void)0 : (void) mexErrMsgTxt(C_STR(__FILE__<<":"<<__LINE__<<": failed assertion `"<<#isOK<<"'"<<std::endl) ) )

#include <igl/matlab/MexStream.h>
#include <igl/matlab/parse_rhs.h>
#include <igl/matlab/prepare_lhs.h>
#include <igl/matlab/validate_arg.h>
#include <igl/list_to_matrix.h>

//bartels
#include <fixed_point_constraint_matrix.h>

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    /* variable declarations here */
    Eigen::SparseMatrix<double> P;

    Eigen::MatrixXd V;
    Eigen::VectorXi fixed_indices;
    
    igl::matlab::parse_rhs_double(prhs+0,V);
    igl::matlab::parse_rhs_index(prhs+1,fixed_indices);
    
    sim::fixed_point_constraint_matrix(P, V, fixed_indices);

    igl::matlab::prepare_lhs_double(P, plhs);
   
}