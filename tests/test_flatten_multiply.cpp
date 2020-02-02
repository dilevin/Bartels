#include <flatten.h>
#include <flatten_multiply.h>

using namespace sim;

template<typename Derived>
void create_matrix(Eigen::DenseBase<Derived> &A) {

    A.setRandom();   
}

int main(int argc, char **argv) {

    std::cout<<"test flatten_multiply\n";

    Flatten_Multiply<Eigen::Matrix3d, Eigen::Matrix3d> A;
    Flatten_Multiply_Right<Eigen::Matrix3d, Eigen::Matrix3d> B; 

    do {
        create_matrix(A);
        B.setRandom();
    } while(A.norm() <= 1 && B.norm() <= 1);

    Eigen::Matrix3d C = A*B;
    
    double test_val = (sim::flatten(C) - A.flatten()*Eigen::Map<Eigen::Matrix<double, 9,1>>(B.data())).norm();


    if( test_val < 1e-8) {
        std::cout<<"PASSED \n";
    } else {
        std::cout<<"FAIL \n";
    }

    test_val = (sim::flatten(C) - B.flatten()*Eigen::Map<Eigen::Matrix<double, 9,1>>(A.data())).norm();

    std::cout<<sim::flatten_eigen(C)<<"\n";

    std::cout<<C<<"\n";

    std::cout<<sim::unflatten_eigen<3,1>(C.row(0))<<"\n";

    if( test_val < 1e-8) {
        std::cout<<"PASSED Reverse\n";
    } else {
        std::cout<<"FAIL Reverse\n";
    }

    std::cout<<"Test unflatten \n";

    test_val = (sim::unflatten<3,3>(sim::flatten(C)) - C).norm();

    if(test_val < 1e-8) {
        std::cout<<"PASSED\n";
    } else {
        std::cout<<"FAIL\n";
    }

    return 0;
}