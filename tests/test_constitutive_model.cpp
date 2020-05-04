#include <linear_tet_dphi_dX.h>
#include <linear_tri2d_dphi_dX.h>
#include <linear_tri2dmesh_dphi_dX.h>
#include <linear_tri2dmesh_corotational_dq.h>
#include <linear_tetmesh_neohookean_dq2.h>
#include <assemble.h>
#include <flatten.h>
#include <flatten_multiply.h>
#include <eval_at_point.h>
#include <linear_tetmesh_dphi_dX.h>
#include <simple_psd_fix.h>

#include <get_data_directory.h>
#include <igl/readMESH.h>
#include <igl/volume.h>

#include <unsupported/Eigen/SparseExtra>

int main(int argc, char **argv) {

    Eigen::MatrixXd V, dphidX,X;
    Eigen::MatrixXi E;
    Eigen::MatrixXi F; 
    Eigen::VectorXd v; //volumes

    igl::readMESH(sim::data_dir()+pathsep+"meshes_mesh"+pathsep+"coarser_bunny.mesh", V, E, F);
    
    igl::volume(V,E, v);
    Eigen::VectorXd density = Eigen::VectorXd::Constant(E.rows(), 0.1);
    
    /*X.resize(E.rows(), 3);

    auto dx = [](auto &a, auto &b, auto c, auto &d) { sim::linear_tet_dphi_dX(a, b, c, d); };
                    
    sim::eval_at_point(dphidX, V, E, dx, Eigen::Matrix43d(), X);*/

    //test some random dphidXs by building random B's and multiplying by q's
    sim::linear_tetmesh_dphi_dX(dphidX, V, E);

    std::cout<<dphidX.rows()<<" "<<dphidX.cols()<<"\n";

    //simulation state
    Eigen::MatrixXd Vt = V.transpose();
    Vt.row(0) *= 2;
    Vt.row(1) *= 4;
    Vt.row(2) *= 3;

    Eigen::VectorXd q = Eigen::Map<Eigen::VectorXd>(Vt.data(), V.size(),1);


    Eigen::Vector12d q_ele;
    Eigen::Vector9d test_I;
    test_I <<2,0,0,0,4,0,0,0,3;

    double error;

    //test deformation gradient calculation 
    for(unsigned int ii=0; ii<E.rows(); ++ii) {
        q_ele << q.segment<3>(3*E(ii,0)), q.segment<3>(3*E(ii,1)), q.segment<3>(3*E(ii,2)), q.segment<3>(3*E(ii,3));
        error = (sim::flatten_multiply_right<Eigen::Matrix<double, 3,4>>(sim::unflatten<4,3>(dphidX.row(ii)))*q_ele - test_I).norm();

        if(fabs(error) > 1e-8) {
            std::cout<<"FAILED\n";
            exit(0);
        }
    }

    std::cout<<"PASSED\n";

    //to do assemble a stiffness matrix for fun

    //d2psi_neo_hookean_dF2(Eigen::DenseBase<HessianType> &ddw, Eigen::DenseBase<HessianType> &F, ParameterType &&C, ParameterType &&D)
    double YM = 6e5; //young's modulus
    double mu = 0.4; //poissons ratio
    double D = 0.5*(YM*mu)/((1.0+mu)*(1.0-2.0*mu));
    double C = 0.5*YM/(2.0*(1.0+mu));
    
    Eigen::SparseMatrixd H, H_test;

    Eigen::MatrixXd params;
    params.resize(E.rows(), 2);
    params.col(0) = Eigen::VectorXd::Constant(E.rows(), C);
    params.col(1) = Eigen::VectorXd::Constant(E.rows(), D);
    sim::linear_tetmesh_neohookean_dq2(H, V, E, q, dphidX, v, params);

    std::cout<<"Loading test data: "<<sim::data_dir()+pathsep+"matrices"+pathsep+"H_neohookean_coarser_bunny.txt"<<"\n";

    bool did_it_load = Eigen::loadMarket(H_test, sim::data_dir()+pathsep+"matrices"+pathsep+"H_neohookean_coarser_bunny.txt");

    if(!did_it_load) {
        std::cout<<"Test data didn't load: quitting \n";
        exit(0);
    }

    //relative error
    error = (H-H_test).norm()/H.coeff(0,0);

    std::cout<<"Test neohookean hessian \n";

    if(error > 1e-8) {
        std::cout<<"FAILED: "<<error<<"\n";
        exit(0);
    }

    std::cout<<"PASSED\n";

    //test 2d gradient on a simple case
    Eigen::MatrixXd V2d(3,2);
    Eigen::MatrixXd dX2d;
    Eigen::MatrixXi E2d(1,3);
    Eigen::MatrixXd params2d;
    Eigen::VectorXd f2d;
    Eigen::VectorXd q2d;

    Eigen::MatrixXd area(1,1);
    area << 68.002;
    V2d << 96.921,       44.047,
           81.5,         37.5,
           87.452,       31.207;

    E2d << 0, 1, 2; 

    params2d.resize(1,2);
    params2d(0,0) =  6.2069e+06;
    params2d(0,1) = 6.8966e+05; 

    Eigen::MatrixXd V2dt = V2d.transpose();

    q2d = Eigen::Map<Eigen::VectorXd>(V2dt.data(), V2d.size(),1);

    sim::linear_tri2dmesh_dphi_dX(dX2d, V2d,  E2d);

    sim::linear_tri2dmesh_corotational_dq(f2d, V2d, E2d, q2d, dX2d, area, params2d); 
                                        
    std::cout<<f2d<<"\n";
}