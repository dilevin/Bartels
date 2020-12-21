#ifndef EIGENTYPES_H
#define EIGENTYPES_H

#include <Eigen/Dense>
#include <Eigen/Sparse>

#include <array>

namespace Eigen {

    //dense types
    using Vector4d = Eigen::Matrix<double,4,1>;
    using Vector6d = Eigen::Matrix<double, 6,1>;
    using Vector9d = Eigen::Matrix<double, 9, 1>;
    using Vector12d = Eigen::Matrix<double, 12,1>;
    
    using Matrix32d = Eigen::Matrix<double, 3,2>;
    using Matrix34d = Eigen::Matrix<double, 3,4>;
    using Matrix36d = Eigen::Matrix<double, 3,6>;
    using Matrix43d = Eigen::Matrix<double, 4,3>;
    using Matrix6d  = Eigen::Matrix<double, 6,6>;
    using Matrix9d = Eigen::Matrix<double, 9, 9>;
    using Matrix12d = Eigen::Matrix<double, 12,12>;
    using Matrix4f = Eigen::Matrix<float, 4,4>;
    
    //some templated aliases that I find useful
    template<typename Scalar>
    using Vector3x = Eigen::Matrix<Scalar, 3, 1>;


    template<typename Scalar>
    using VectorXx = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;

    template<typename Scalar>
    using Matrix23x = Eigen::Matrix<Scalar, 2,3>;

    template<typename Scalar>
    using Matrix32x = Eigen::Matrix<Scalar, 3,2>;

    template<typename Scalar>
    using Matrix3x = Eigen::Matrix<Scalar, 3,3>;

    template<typename Scalar>
    using Matrix43x = Eigen::Matrix<Scalar, 4,3>;
    
    template<typename Scalar>
    using Matrix6x = Eigen::Matrix<Scalar, 6,6>;

    template<typename Scalar>
    using Matrix9x = Eigen::Matrix<Scalar, 9,9>;

    template<typename Scalar>
    using Matrix912 = Eigen::Matrix<Scalar, 9,12>;

    template<typename Scalar>
    using Matrix12x = Eigen::Matrix<Scalar, 12,12>;
    
    template<typename Scalar>
    using MatrixXx = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    
    template<typename Scalar>
    using Vector6x = Eigen::Matrix<Scalar, 6,1>;
    
    template<typename Scalar>
    using Vector9x = Eigen::Matrix<Scalar, 9,1>;

    template<typename Scalar>
    using Vector12x = Eigen::Matrix<Scalar, 12,1>;
    
    //sparse types
    using SparseMatrixd = Eigen::SparseMatrix<double>;

    //tensor types (which are just arrays of matrices)
    using Tensor333d = std::array<std::array<Eigen::Vector3d,3>, 3>;
    using Tensor3333d = std::array<std::array<Eigen::Matrix3d,3>, 3>;

    template<typename Scalar>
    using Tensor333x = std::array<std::array<Eigen::Vector3x<Scalar>,3>, 3>;

    template<typename Scalar>
    using Tensor3333x = std::array<std::array<Eigen::Matrix3x<Scalar>,3>, 3>;

}

inline double stablePow(double a, double b) {        
    return static_cast<double> (std::pow(std::cbrt(static_cast<double>(a)),static_cast<double>(b)));
}

inline void inverse33(Eigen::Ref<Eigen::Matrix3d> result, Eigen::Ref<const Eigen::Matrix3d> A) {
    double determinant =    +A(0,0)*(A(1,1)*A(2,2)-A(2,1)*A(1,2))
                            -A(0,1)*(A(1,0)*A(2,2)-A(1,2)*A(2,0))
                            +A(0,2)*(A(1,0)*A(2,1)-A(1,1)*A(2,0));
    double invdet = 1/determinant;
    result(0,0) =  (A(1,1)*A(2,2)-A(2,1)*A(1,2))*invdet;
    result(1,0) = -(A(0,1)*A(2,2)-A(0,2)*A(2,1))*invdet;
    result(2,0) =  (A(0,1)*A(1,2)-A(0,2)*A(1,1))*invdet;
    result(0,1) = -(A(1,0)*A(2,2)-A(1,2)*A(2,0))*invdet;
    result(1,1) =  (A(0,0)*A(2,2)-A(0,2)*A(2,0))*invdet;
    result(2,1) = -(A(0,0)*A(1,2)-A(1,0)*A(0,2))*invdet;
    result(0,2) =  (A(1,0)*A(2,1)-A(2,0)*A(1,1))*invdet;
    result(1,2) = -(A(0,0)*A(2,1)-A(2,0)*A(0,1))*invdet;
    result(2,2) =  (A(0,0)*A(1,1)-A(1,0)*A(0,1))*invdet;
    result.transposeInPlace();
}

inline void inverse22(Eigen::Ref<Eigen::Matrix2d> result, Eigen::Ref<const Eigen::Matrix2d> A) {
    double determinant = A(0,0)*A(1,1) - A(0,1)*A(1,0);

    double invdet = 1./determinant;
    result(0,0) =  A(1,1)*invdet;
    result(1,0) = -A(1,0)*invdet;
    result(0,1) = -A(0,1)*invdet;
    result(1,1) =  A(0,0)*invdet;

}

auto default_callback = [](auto &element_matrix){};

auto default_linesearch_callback = [](auto &x) {};

//include flatten operations
#include <flatten.h>
#include <flatten_multiply.h>

#endif 
