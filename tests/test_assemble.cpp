#include <get_data_directory.h>
#include <linear_tet_mass_matrix.h>
#include <assemble.h>

#include <unsupported/Eigen/SparseExtra>

//libigl stuff
#include <igl/readMESH.h>
#include <igl/volume.h>

int main(int argc, char **argv) {



    Eigen::SparseMatrixd M; //assembled 
    Eigen::SparseMatrixd M_test; //test data 
    Eigen::Matrix1212d Me = Eigen::Matrix1212d::Identity(); //tmp storage

    Eigen::MatrixXd V, quad_points, quad_weights; 
    Eigen::MatrixXi E;
    Eigen::MatrixXi F; 
    Eigen::VectorXd v; //volumes


    /*V.resize(5,3);
    E.resize(2,4);

    V <<    0.,      0.,      0.,
            1.,      0.,      1.,
            1.,      1.,      0.,
            1.,      0.,     -1.,
            2.,      0.,      0.;

    E << 0, 1, 2, 3,
         4, 3, 2, 1; */

    igl::readMESH(sim::data_dir()+pathsep+"meshes_mesh"+pathsep+"coarser_bunny.mesh", V, E, F);
    igl::volume(V,E, v);

    //assemble function
    auto assemble_func = [](Eigen::DenseBase<Eigen::Matrix1212d> &M,  Eigen::Ref<const Eigen::RowVectorXi> e, Eigen::Ref<const Eigen::RowVectorXd> volume) { sim::linear_tet_mass_matrix(M, e, 0.1, volume(0)); };
    
    /*Eigen::SparseMatrixBase<DerivedRet> &assembled, 
                unsigned int rows, unsigned int cols, 
                Eigen::Ref<Eigen::MatrixXi> E_from,  
                Eigen::Ref<Eigen::MatrixXi> E_to,  
                Func func, Params && ... params,
                Eigen::MatrixBase<DerivedTmp> &tmp*/
    
    sim::assemble(M, 3*V.rows(), 3*V.rows(), E, E, assemble_func, Me, v);

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
    

    return 0;
}

