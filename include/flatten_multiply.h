#ifndef SIM_FLATTEN_MULTIPLY_H
#define SIM_FLATTEN_MULTIPLY_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

//Given an expression C = A*B, return a matrix A^* s.t
//X(:) = (A^*)*B(:), here I am using matlab colon operators to denote flattening a matrix

template<typename A, typename B>
class Flatten_Multiply 
{
public:
    template<typename ...Args>
    inline Flatten_Multiply(Args &&...args) {
        std::cout<<"ERROR: Generic flatten multiply not implemented \n";
        exit(1);
    }

protected:
private:
};

//Specializations
//A is a 3x3 matrix, B is 3x3 
template<typename Scalar>
class Flatten_Multiply<Eigen::Matrix<Scalar, 3,3>, Eigen::Matrix<Scalar, 3,3> > :
    public Eigen::Matrix<Scalar, 3,3>
{
public:
    
    inline Flatten_Multiply() : Eigen::Matrix<Scalar, 3,3>() {
        
    }

    inline Eigen::Matrix<Scalar, 9,9> > & flatten() {

        Eigen::Matrix<Scalar, 9,9> M;
        M << A(0,0),  A(0,1),     A(0,2),     0,      0,      0,      0,      0,      0,
                   0,       0,          0           A(1,0), A(1,1), A(1,2), 0,      0,      0,
                   0,       0,          0           0,      0,      0,      A(2,0), A(2,1), A(2,2), 
                   A(0,0),  A(0,1),     A(0,2),     0,      0,      0,      0,      0,      0,
                   0,       0,          0           A(1,0), A(1,1), A(1,2), 0,      0,      0,
                   0,       0,          0           0,      0,      0,      A(2,0), A(2,1), A(2,2), 
                   A(0,0),  A(0,1),     A(0,2),     0,      0,      0,      0,      0,      0,
                   0,       0,          0           A(1,0), A(1,1), A(1,2), 0,      0,      0,
                   0,       0,          0           0,      0,      0,      A(2,0), A(2,1), A(2,2);

        return M; 
        
    }

protected:

private:
};

#ifndef SIM_STATIC_LIBRARY
# include<../src/flatten_multiply.cpp>
#endif

#endif