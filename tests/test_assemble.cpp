#include <quadrature_rule_single_point.h> 
#include <assemble.h>

int main(int argc, char **argv) {

    Eigen::MatrixXd V; 
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

    //make some integration points


    //convert from "barycentric" coordinates to per-element coordinates ?

    //assemble function

    std::cout<<"Test Assemble Sparse Matrix \n";
    
    std::cout<<"Test Assemble Sparse Matrix from Flatten_Multiply \n";

    std::cout<<"Test Assemble Vector \n";
    
    return 0;
}