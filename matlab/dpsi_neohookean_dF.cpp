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

//bartels
#include <BlockDiagonalMatrix.h>
#include <dpsi_neohookean_dF.h>
#include "check_arguments.h"

#ifdef BARTELS_USE_OPENMP
#include <omp.h>
#endif

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
                     
    auto MAT_DYNAMIC =  sim::Argument::DYNAMIC;

    /* variable declarations here */
    Eigen::VectorXd g;

    Eigen::MatrixXi E;
    Eigen::MatrixXd F, params;

    igl::matlab::parse_rhs_index(prhs+0,E);

    /* Validate Arguments Here */
    //first check I got sent some elements
    sim::validate_arguments({sim::Argument("double", {{sim::Dim(MAT_DYNAMIC)}, {sim::Dim(MAT_DYNAMIC)}}, false),
                             sim::Argument("double", {{sim::Dim(0,0)}, {sim::Dim(9)}}, false),
                             sim::Argument("double", {{sim::Dim(0,0)}, {sim::Dim(2)}}, false)}, 
                             nrhs, prhs);

    igl::matlab::parse_rhs_double(prhs+1, F);
    igl::matlab::parse_rhs_double(prhs+2, params);
    
    g.resize(9*E.rows()); 
    
    #pragma omp parallel
    {
        
        Eigen::Vector9d gele;
    
        #pragma omp for schedule(static)
        for(unsigned int ii=0; ii<E.rows(); ++ii) {
            sim::dpsi_neohookean_dF(gele, sim::unflatten<3,3>(F.row(ii)), params.row(ii)); 
            g.segment(9*ii, 9) = gele;
        }
        
    }

    igl::matlab::prepare_lhs_double(g, plhs);
   
}