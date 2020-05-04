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
#include <linear_tri2dmesh_stvk_dq2.h>
#include <simple_psd_fix.h>

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    /* variable declarations here */
    Eigen::SparseMatrix<double> H;

    Eigen::MatrixXd V;
    Eigen::MatrixXi E;
    Eigen::VectorXd q;
    Eigen::MatrixXd dphidX, params;
    Eigen::VectorXd volumes; 

    igl::matlab::parse_rhs_double(prhs+0,V);
    igl::matlab::parse_rhs_index(prhs+1,E);
    igl::matlab::parse_rhs_index(prhs+2,q);
    igl::matlab::parse_rhs_double(prhs+3, dphidX);
    igl::matlab::parse_rhs_double(prhs+4, volumes);
    igl::matlab::parse_rhs_double(prhs+5, params);

    if(nrhs > 6) {
        //spd fix
        sim::linear_tri2dmesh_stvk_dq2(H, V, E, q, dphidX, volumes,  params, [](auto &a) {sim::simple_psd_fix(a, 1e-3);});
    } else {
        sim::linear_tri2dmesh_stvk_dq2(H, V, E, q, dphidX, volumes,  params);
    }

    igl::matlab::prepare_lhs_double(H, plhs);
   
}