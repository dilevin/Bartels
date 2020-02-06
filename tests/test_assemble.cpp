#include <get_data_directory.h>
#include <linear_tetmesh_const_ext_force.h>
#include <linear_tetmesh_mass_matrix.h>

#include <unsupported/Eigen/SparseExtra>

//libigl stuff
#include <igl/readMESH.h>
#include <igl/volume.h>

int main(int argc, char **argv) {



    Eigen::SparseMatrixd M; //assembled 
    Eigen::VectorXd f; //assembled forces 
    Eigen::SparseMatrixd M_test; //test data 
    Eigen::Matrix12d Me = Eigen::Matrix12d::Identity(); //tmp storage

    Eigen::MatrixXd V;
    Eigen::MatrixXi E;
    Eigen::MatrixXi F; 
    Eigen::VectorXd v; //volumes

    igl::readMESH(sim::data_dir()+pathsep+"meshes_mesh"+pathsep+"coarser_bunny.mesh", V, E, F);
    
    igl::volume(V,E, v);
    Eigen::VectorXd density = Eigen::VectorXd::Constant(E.rows(), 0.1);
    sim::linear_tetmesh_mass_matrix(M, V, E,density, v);

    std::cout<<"Loading test data: "<<sim::data_dir()+pathsep+"matrices"+pathsep+"M_coarse_bunny.txt"<<"\n";

    bool did_it_load = Eigen::loadMarket(M_test, sim::data_dir()+pathsep+"matrices"+pathsep+"M_coarse_bunny.txt");

    if(!did_it_load) {
        std::cout<<"Test data didn't load: quitting \n";
        exit(0);
    }

    std::cout<<"Test Assemble Sparse Matrix \n";
    double error = (M-M_test).norm();

    if(error > 1e-8) {
        std::cout<<"Error: "<<error<<" is too high, assembler failed: quitting \n";
        exit(0);
    }

    std::cout<<"Assemble Sparse Matrix: PASSED \n";

    std::cout<<"Test Assemble Vector \n";
    
    //check if assembled gravity vector = M*g 
    //assemble function
    Eigen::Vector3d g; //acceleration due to gravity
    //Eigen::Vector12d f_tmp;
    g << 0, -9.8, 0;

    ///auto assemble_vec_func = [&g](Eigen::DenseBase<Eigen::Vector12d> &f,  Eigen::Ref<const Eigen::RowVectorXi> e, Eigen::Ref<const Eigen::RowVectorXd> volume) { sim::linear_tet_const_ext_force(f, e, volume(0), 0.1*g); };
    
    //sim::assemble(f, 3*V.rows(), E, E, assemble_vec_func, f_tmp, v);

    sim::linear_tetmesh_const_ext_force(f, V, E, v, 0.1*g);
    error = (f - M*g.replicate(V.rows(),1)).norm();

    //std::cout<<f<<"\n";
    if(error > 1e-8) {
        std::cout<<"Error: "<<error<<" is too high, assemble vector failed: quitting \n";
        exit(0);
    }

    std::cout<<"Assemble Vector: PASSED \n";


    return 0;
}

