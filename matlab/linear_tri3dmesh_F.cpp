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
#include "EigenTypes.h"
#include <BartelsTypes.h>
#include <eval_at_point.h>

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    /* variable declarations here */

    Eigen::MatrixXd V;
    Eigen::MatrixXi E;
    Eigen::VectorXd q;
    Eigen::MatrixXd dphidX;
    Eigen::MatrixXd N;
    Eigen::MatrixXd n;
    Eigen::MatrixXd F;

    igl::matlab::parse_rhs_double(prhs+0,V);
    igl::matlab::parse_rhs_index(prhs+1,E);
    igl::matlab::parse_rhs_double(prhs+2,q);
    igl::matlab::parse_rhs_double(prhs+3, dphidX);
    igl::matlab::parse_rhs_double(prhs+4,N);
    igl::matlab::parse_rhs_double(prhs+5,n);
    
    auto compute_F = [](auto &tmp, auto &q0, auto &element, auto &x, auto &dphidX0, auto &N0, auto &n0)
    {
        Eigen::Vector9d qe;
        qe << q0.segment(3*element(0),3), q0.segment(3*element(1),3), q0.segment(3*element(2),3);
        
        tmp = sim::unflatten<3,3>(qe)*sim::unflatten<3,3>(dphidX0) + n0.transpose()*N0;
    };
    
    Eigen::Matrix<double, 3,3> tmp_F; //tmp storage for eval points

    //sort of hacking eval_at_point to do what I want here
    sim::eval_at_point(F, q, E, compute_F, tmp_F, E, dphidX, N, n);

    igl::matlab::prepare_lhs_double(F, plhs);
   
}