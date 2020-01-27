#include <linear_tet_mass_matrix.h>
#include <assemble.h>

int main(int argc, char **argv) {

    Eigen::SparseMatrixd M; //assembled 
    Eigen::Matrix1212d Me = Eigen::Matrix1212d::Identity(); //tmp storage

    Eigen::MatrixXd V, quad_points, quad_weights; 
    Eigen::MatrixXi E;
    
    V.resize(5,3);
    E.resize(2,4);

    V <<    0.,      0.,      0.,
            1.,      0.,      1.,
            1.,      1.,      0.,
            1.,      0.,     -1.,
            2.,      0.,      0.;

    E << 0, 1, 2, 3,
         4, 3, 2, 1; 

    //assemble function
    auto assemble_func = [](Eigen::DenseBase<Eigen::Matrix1212d> &M,  Eigen::Ref<const Eigen::RowVectorXi> e) { sim::linear_tet_mass_matrix(M, e, 1.0, 1.0); };
    /*Eigen::SparseMatrixBase<DerivedRet> &assembled, 
                unsigned int rows, unsigned int cols, 
                Eigen::Ref<Eigen::MatrixXi> E_from,  
                Eigen::Ref<Eigen::MatrixXi> E_to,  
                Func func, Params && ... params,
                Eigen::MatrixBase<DerivedTmp> &tmp*/
    
    sim::assemble(M, 3*V.rows(), 3*V.rows(), E, E, assemble_func, Me);
    

    std::cout<<"Test Assemble Sparse Matrix \n";
    
    std::cout<<"Test Assemble Sparse Matrix from Flatten_Multiply \n";

    std::cout<<"Test Assemble Vector \n";
    
    return 0;
}

