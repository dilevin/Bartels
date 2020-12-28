#include <iostream>
#include <EigenTypes.h>
#include <BlockDiagonalMatrix.h>
#include <igl/Timer.H>
#include <PardisoOpenSource.h>

int main(int argc, char **argv) {

    #ifdef BARTELS_USE_PARDISO

    std::cout<<"Test Pardiso\n";

    Eigen::SparseMatrix<double, Eigen::RowMajor> A;
    Eigen::MatrixXd b;

    b.resize(100,1);
    b.setRandom();
    A.resize(100,100);
    A.setIdentity();

    Eigen::PardisoLU<Eigen::SparseMatrix<double, Eigen::RowMajor> > test(8);
    test.compute(A);

    if(test.info() != Eigen::Success) {
        std::cout<<"Problem\n";
    } else {
        std::cout<<"Success\n";
    }

    Eigen::MatrixXd x = test.solve(b);

    if(test.info() != Eigen::Success) {
        std::cout<<"Problem\n";
    } else {
        std::cout<<"Success\n";
    }

    std::cout<<"Error: "<<(x-b).norm()<<"\n";
    #endif

    return 0;


}