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
#include <linear_tri2dmesh_linear_elasticity_dq2.h>

/* The gateway function */
//this is gross but I'm working quickly.
//should really have methods to compute the constitutive model and strain matrices
//get to these later once everything else is sorted out.
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    /* variable declarations here */
    Eigen::MatrixXx<double> cauchy_stress;
    

    Eigen::MatrixXd V;
    Eigen::MatrixXi E;
    Eigen::VectorXd u;
    Eigen::MatrixXd dXinv, params;
    Eigen::VectorXd volumes;

    igl::matlab::parse_rhs_double(prhs+0,V);
    igl::matlab::parse_rhs_index(prhs+1,E);
    igl::matlab::parse_rhs_index(prhs+2,u);
    igl::matlab::parse_rhs_double(prhs+3, dXinv);
    igl::matlab::parse_rhs_double(prhs+4, volumes);
    igl::matlab::parse_rhs_double(prhs+5, params);

    cauchy_stress.resize(E.rows(), 6);

    Eigen::Matrix3x<double> F = Eigen::Matrix3x<double>::Zero();
    Eigen::Matrix6x<double> dF2; 
    Eigen::Matrix<double, 9,6> P;
    Eigen::Matrix<double, 6,9> P2; //collect up off diagonal shears to reduce from 6 to 9
    Eigen::Vector6x<double> ue;

    P<<1, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0;

    P2<<1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 1, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1, 0, 0,
        0, 1, 0, 1, 0, 0, 0, 0, 0;

    for(unsigned int ii=0; ii<E.rows(); ++ii) {

        F.block(0,0,3,2) = sim::unflatten<3,2>(dXinv.row(ii)); 

        Eigen::Matrix<double, 6,6> B = P2*sim::flatten_multiply_right<Eigen::Matrix3d>(F)*P;

        ue << u.segment(2*E(ii,0),2), u.segment(2*E(ii,1),2), u.segment(2*E(ii,2),2);

        //grab per element positions
        sim::d2psi_linear_elasticity_de2(dF2, params.row(ii));

        cauchy_stress.row(ii) = -volumes(ii)*(dF2*B*ue).transpose();

    }

    igl::matlab::prepare_lhs_double(cauchy_stress, plhs);
   
}