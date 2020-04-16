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
#include <BlockDiagonalMatrix.h>
#include <d2psi_neohookean_dF2.h>

/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    /* variable declarations here */
    Eigen::BlockDiagonal<double> H;

    Eigen::MatrixXi E;
    Eigen::MatrixXd F, params;

    igl::matlab::parse_rhs_index(prhs+0,E);
    igl::matlab::parse_rhs_double(prhs+1, F);
    igl::matlab::parse_rhs_double(prhs+2, params);
    
    //resize(num_blocks, block rows)
    H.resize(E.rows(), 9); 
    Eigen::Matrix9d Hele;

    for(unsigned int ii=0; ii<E.rows(); ++ii) {
        sim::d2psi_neohookean_dF2(Hele, sim::unflatten<3,3>(F.row(ii)), params.row(ii)); 
        H.diagonalBlock(ii) = Hele;
    }

    Eigen::SparseMatrix<double> H_sparse = H;
    igl::matlab::prepare_lhs_double(H_sparse, plhs);
   
}