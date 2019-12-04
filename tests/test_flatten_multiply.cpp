#include <flatten_multiply.h>

using namespace sim;

template<typename Derived>
void create_matrix(Eigen::DenseBase<Derived> &A) {

    A.setRandom();   
}

int main(int argc, char **argv) {

    std::cout<<"test flatten_multiply\n";

    Flatten_Multiply<Eigen::Matrix3d, Eigen::Matrix3d> A;
    Eigen::Matrix3d B; 

    do {
        create_matrix(A);
        B.setRandom();
    } while(A.norm() <= 1 && B.norm() <= 1);

    Eigen::Matrix3d C = A*B;
    Eigen::Matrix<double, 9,1> B1 = Eigen::Map<Eigen::Matrix<double, 9,1>>(B.data());
    double test_val = (Eigen::Map<Eigen::Matrix<double,9,1>>(C.data()) - A.flatten()*Eigen::Map<Eigen::Matrix<double, 9,1>>(B.data())).norm();

    if( test_val < 1e-8) {
        std::cout<<"Success \n";
    } else {
        std::cout<<"Fail \n";
    }

    return 0;
}