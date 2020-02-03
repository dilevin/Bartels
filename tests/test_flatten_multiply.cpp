#include <flatten.h>
#include <flatten_multiply.h>

using namespace sim;

template<typename Derived>
void create_matrix(Eigen::DenseBase<Derived> &A) {

    A.setRandom();   
}

int main(int argc, char **argv) {

    std::cout<<"test flatten_multiply\n";

    Eigen::Matrix3d A;
    Eigen::Matrix3d B; 

    do {
        create_matrix(A);
        B.setRandom();
    } while(A.norm() <= 1 && B.norm() <= 1);

    Eigen::Matrix3d C = A*B;
    
    double test_val = (sim::flatten(C) - flatten_multiply<Eigen::Matrix3d>(A)*Eigen::Map<Eigen::Matrix<double, 9,1>>(B.data())).norm();


    if( test_val < 1e-8) {
        std::cout<<"PASSED \n";
    } else {
        std::cout<<"FAIL \n";
    }

    test_val = (sim::flatten(C) - flatten_multiply_right<Eigen::Matrix3d>(B)*Eigen::Map<Eigen::Matrix<double, 9,1>>(A.data())).norm();

    if( test_val < 1e-8) {
        std::cout<<"PASSED Reverse\n";
    } else {
        std::cout<<"FAIL Reverse\n";
    }

    test_val = (sim::unflatten<3,3>(sim::flatten(C)) - C).norm();

    if(test_val < 1e-8) {
        std::cout<<"PASSED\n";
    } else {
        std::cout<<"FAIL\n";
    }

    return 0;
}