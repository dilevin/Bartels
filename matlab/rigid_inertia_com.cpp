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
#include <rigid_inertia_com.h>

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    /* variable declarations here */
    Eigen::Matrix3d I; 
    Eigen::Vector3d com; 
    Eigen::Matrix<double, 1,1> mass;
                           

    Eigen::MatrixXd V;
    Eigen::MatrixXi E;
    Eigen::Matrix<double, 1,1> density;

    igl::matlab::parse_rhs_double(prhs+0,V);
    igl::matlab::parse_rhs_index(prhs+1,E);
    igl::matlab::parse_rhs_double(prhs+2,density);
    
    sim::rigid_inertia_com(I,com, mass(0,0), V, E, density(0,0));

    igl::matlab::prepare_lhs_double(I, plhs+0);
    igl::matlab::prepare_lhs_double(com, plhs+1);
    igl::matlab::prepare_lhs_double(mass, plhs+2);
   
}