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
#include <linear_tri2dmesh_arap_q.h>

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    /* variable declarations here */
    double energy;

    Eigen::MatrixXd V;
    Eigen::MatrixXi E;
    Eigen::VectorXd q;
    Eigen::MatrixXd dXinv, params;
    Eigen::VectorXd volumes; 

    igl::matlab::parse_rhs_double(prhs+0,V);
    igl::matlab::parse_rhs_index(prhs+1,E);
    igl::matlab::parse_rhs_index(prhs+2,q);
    igl::matlab::parse_rhs_double(prhs+3, dXinv);
    igl::matlab::parse_rhs_double(prhs+4, volumes);
    igl::matlab::parse_rhs_double(prhs+5, params);

    plhs[0] = mxCreateDoubleMatrix((mwSize)1, (mwSize)1, mxREAL);

    mxGetPr(plhs[0])[0] = sim::linear_tri2dmesh_arap_q(V, E, q, dXinv, volumes,  params);
   
}