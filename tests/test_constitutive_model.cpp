#include <linear_tet_dphi_dX.h>
#include <flatten.h>
#include <flatten_multiply.h>
#include <eval_at_point.h>

#include <get_data_directory.h>
#include <igl/readMESH.h>
#include <igl/volume.h>

int main(int argc, char **argv) {

    Eigen::MatrixXd V, dXinv,X;
    Eigen::MatrixXi E;
    Eigen::MatrixXi F; 
    Eigen::VectorXd v; //volumes

    igl::readMESH(sim::data_dir()+pathsep+"meshes_mesh"+pathsep+"coarser_bunny.mesh", V, E, F);
    
    igl::volume(V,E, v);
    Eigen::VectorXd density = Eigen::VectorXd::Constant(E.rows(), 0.1);
    
    X.resize(E.rows(), 3);

    auto dx = [](auto &a, auto &b, auto c, auto &d) { sim::linear_tet_dphi_dX(a, b, c, d); };
                    
    sim::eval_at_point(dXinv, V, E, dx, Eigen::Matrix43d(), X);

    //test some random dXinvs by building random B's and multiplying by q's
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
        error = (sim::flatten_multiply_right<Eigen::Matrix<double, 3,4>>(sim::unflatten<4,3>(dXinv.row(ii)))*q_ele - test_I).norm();

        if(fabs(error) > 1e-8) {
            std::cout<<"FAILED\n";
            exit(0);
        }
    }

    std::cout<<"PASSED\n";

    //to do assemble a stiffness matrix for fun

    //assemble the force vector (which should be zero in the underformed state)

}