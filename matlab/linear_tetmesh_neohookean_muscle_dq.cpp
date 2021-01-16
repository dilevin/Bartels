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
#include <matrix.h>

//bartels
#include <linear_tet_neohookean_dq.h>
#include <dpsi_muscle_fiber_dF.h>
#include <linear_tetmesh_generic_elastic_dq.h>



/* The gateway function */
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[]) {
    
    //variable for return
    Eigen::VectorXd g;


    Eigen::MatrixXd V;
    Eigen::MatrixXi E;
    Eigen::VectorXd q;
    Eigen::MatrixXd dphidX, params_nh, params_a, directions;
    Eigen::VectorXd volumes; 

    igl::matlab::parse_rhs_double(prhs+0,V);
    igl::matlab::parse_rhs_index(prhs+1,E);
    igl::matlab::parse_rhs_index(prhs+2,q);
    igl::matlab::parse_rhs_double(prhs+3, dphidX);
    igl::matlab::parse_rhs_double(prhs+4, volumes);
    igl::matlab::parse_rhs_double(prhs+5, directions);
    igl::matlab::parse_rhs_double(prhs+6, params_nh);
    igl::matlab::parse_rhs_double(prhs+7, params_a);

    //mxGetPr(plhs[0])[0] = sim::linear_tetmesh_neohookean_q(V, E, q, dphidX, volumes,  params);
    //use my new (at time of writing) generic elasticity method (exciting!)

    //just so I remember what this lambda has to look like
    //return mat_func(q, e, F, sim::unflatten<4,3>(dphidX), params..., volume(0));
    auto neohookean_muscle = [](auto &g, const auto &q, const auto &e, const auto &F, const auto &dphidX, const auto& direction, const auto &params_nh, const auto &params_a, const auto &volume) {

        Eigen::Vector9d g_fiber;

        sim::linear_tet_neohookean_dq(g, q,e,dphidX, params_nh, volume);

        Eigen::Matrix<double, 9,12> B = sim::flatten_multiply_right<Eigen::Matrix<double, 3,4> >(dphidX);
        
        //local positions
        Eigen::Vector12x<double> qe;
        qe << q.segment(3*e(0),3), q.segment(3*e(1),3), q.segment(3*e(2),3), q.segment(3*e(3),3);

        sim::dpsi_muscle_fiber_dF(g_fiber, sim::unflatten<3,3>(B*qe), direction.transpose(), params_a);
        
        g += B.transpose()*g_fiber*volume;


    };
    
    sim::linear_tetmesh_generic_elastic_dq(g, V,E,q, dphidX, dphidX, volumes, neohookean_muscle, directions, params_nh, params_a);

    igl::matlab::prepare_lhs_double(g, plhs);

}