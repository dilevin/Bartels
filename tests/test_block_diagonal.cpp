#include <EigenTypes.h>
#include <BlockDiagonalMatrix.h>
#include <iostream>

int main(int argc, char **argv) {

    std::cout<<"Test Block Diagonal Matrix \n";

    Eigen::BlockDiagonal<double, Eigen::Dynamic> block_diag, bd2;
    block_diag.resize(2,4);
    bd2.resize(2,4);
    
    block_diag.diagonalBlock(0).setIdentity();
    block_diag.diagonalBlock(1).setConstant(25.0);

    bd2.diagonalBlock(0).setIdentity();
    bd2.diagonalBlock(1).setConstant(25.0);

    std::cout<<"Stuff: "<<block_diag.nonZeros()<<"\n";
    block_diag.resize(2,4);

    std::cout<<block_diag<<"\n";

    std::cout<<block_diag*bd2<<"\n";

}