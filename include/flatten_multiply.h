#ifndef SIM_FLATTEN_MULTIPLY_H
#define SIM_FLATTEN_MULTIPLY_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

#include <iostream>

namespace sim {

    //Given an expression C = A*B, return a matrix A^* s.t
    //X(:) = (A^*)*B(:), here I am using matlab colon operators to denote flattening a matrix
    template<typename ...Params>
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
        
        typedef Eigen::Matrix<Scalar,3,3> Base;

        inline Flatten_Multiply() : Eigen::Matrix<Scalar, 3,3>() {
            
        }

        // This constructor allows you to construct MyVectorType from Eigen expressions
        template<typename OtherDerived>
        Flatten_Multiply(const Eigen::MatrixBase<OtherDerived>& other)
            : Eigen::Matrix<Scalar,3,3>(other)
        { }
        // This method allows you to assign Eigen expressions to MyVectorType
        template<typename OtherDerived>
        Flatten_Multiply<Eigen::Matrix<Scalar, 3,3>, Eigen::Matrix<Scalar, 3,3> > & operator= (const Eigen::MatrixBase <OtherDerived>& other)
        {
            this->Base::operator=(other);
            return *this;
        }

        inline Eigen::Matrix<Scalar, 9,9> flatten() {

            Eigen::Matrix<Scalar, 9,9> M;
            M << (*this)(0,0), (*this)(0,1), (*this)(0,2),        0,            0,           0,            0,            0,           0,
                (*this)(1,0), (*this)(1,1), (*this)(1,2),        0,            0,           0,            0,            0,           0,
                (*this)(2,0), (*this)(2,1), (*this)(2,2),        0,            0,           0,            0,            0,           0,
                    0,       0,                0,             (*this)(0,0), (*this)(0,1), (*this)(0,2), 0,            0,           0,
                    0,       0,                0,             (*this)(1,0), (*this)(1,1), (*this)(1,2), 0,            0,           0,
                    0,       0,                0,             (*this)(2,0), (*this)(2,1), (*this)(2,2), 0,            0,           0,
                    0,       0,                0,             0,             0,            0,           (*this)(0,0), (*this)(0,1), (*this)(0,2),
                    0,       0,                0,             0,             0,            0,           (*this)(1,0), (*this)(1,1), (*this)(1,2),
                    0,       0,                0,             0,             0,            0,           (*this)(2,0), (*this)(2,1), (*this)(2,2);

            return M; 
            
        }

    protected:

    private:
    };

}
#ifndef SIM_STATIC_LIBRARY
# include<../src/flatten_multiply.cpp>
#endif

#endif