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

    template<typename ...Params>
    class Flatten_Multiply_Right
    {
    public:
        template<typename ...Args>
        inline Flatten_Multiply_Right(Args &&...args) {
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

    //Specializations
    //A is a 3x3 matrix, B is 3x3 
    template<typename Scalar>
    class Flatten_Multiply_Right<Eigen::Matrix<Scalar, 3,3>, Eigen::Matrix<Scalar, 3,3> > :
        public Eigen::Matrix<Scalar, 3,3>
    {
    public:
        
        typedef Eigen::Matrix<Scalar,3,3> Base;

        inline Flatten_Multiply_Right() : Eigen::Matrix<Scalar, 3,3>() {
            
        }

        // This constructor allows you to construct MyVectorType from Eigen expressions
        template<typename OtherDerived>
        Flatten_Multiply_Right(const Eigen::MatrixBase<OtherDerived>& other)
            : Eigen::Matrix<Scalar,3,3>(other)
        { }
        // This method allows you to assign Eigen expressions to MyVectorType
        template<typename OtherDerived>
        Flatten_Multiply_Right<Eigen::Matrix<Scalar, 3,3>, Eigen::Matrix<Scalar, 3,3> > & operator= (const Eigen::MatrixBase <OtherDerived>& other)
        {
            this->Base::operator=(other);
            return *this;
        }

        //flatten so you can multiply in reverse order
        //i.e vec(A*B) = B.flatten_r()*A
        inline Eigen::Matrix<Scalar, 9,9> flatten() {
             Eigen::Matrix<Scalar, 9,9> M;
           M << (*this)(0,0),0,                0,         (*this)(1,0),        0,           0,         (*this)(2,0),    0,           0,
                    0,       (*this)(0,0),     0,            0,         (*this)(1,0),       0,           0,         (*this)(2,0),    0,          
                    0,       0,            (*this)(0,0),     0,                0,         (*this)(1,0),  0,           0,         (*this)(2,0),      
                    (*this)(0,1),0,                0,         (*this)(1,1),        0,           0,         (*this)(2,1),    0,           0,
                    0,       (*this)(0,1),     0,            0,         (*this)(1,1),       0,           0,         (*this)(2,1),    0,          
                    0,       0,            (*this)(0,1),     0,                0,         (*this)(1,1),  0,           0,         (*this)(2,1),      
                    (*this)(0,2),0,                0,         (*this)(1,2),        0,           0,         (*this)(2,2),    0,           0,
                    0,       (*this)(0,2),     0,            0,         (*this)(1,2),       0,           0,         (*this)(2,2),    0,          
                    0,       0,            (*this)(0,2),     0,                0,         (*this)(1,2),  0,           0,         (*this)(2,2);      
            return M; 

        }

    protected:

    private:

    };

    //A is a 3x4 matrix, B is 4x3 
    template<typename Scalar>
    class Flatten_Multiply_Right<Eigen::Matrix<Scalar, 3,4>, Eigen::Matrix<Scalar, 4,3> > :
        public Eigen::Matrix<Scalar, 4,3>
    {
    public:
        
        typedef Eigen::Matrix<Scalar,4,3> Base;

        inline Flatten_Multiply_Right() : Eigen::Matrix<Scalar, 4,3>() {
            
        }

        // This constructor allows you to construct MyVectorType from Eigen expressions
        template<typename OtherDerived>
        Flatten_Multiply_Right(const Eigen::MatrixBase<OtherDerived>& other)
            : Eigen::Matrix<Scalar,4,3>(other)
        { }
        // This method allows you to assign Eigen expressions to MyVectorType
        template<typename OtherDerived>
        Flatten_Multiply_Right<Eigen::Matrix<Scalar, 4,3>, Eigen::Matrix<Scalar, 4,3> > & operator= (const Eigen::MatrixBase <OtherDerived>& other)
        {
            this->Base::operator=(other);
            return *this;
        }

        //flatten so you can multiply in reverse order
        //i.e vec(A*B) = B.flatten_r()*A
        inline Eigen::Matrix<Scalar, 9,12> flatten() {
             Eigen::Matrix<Scalar, 9,12> M;
           M << (*this)(0,0),0,                0,         (*this)(1,0),        0,           0,         (*this)(2,0),    0,           0,         (*this)(3,0),    0,           0,
                    0,       (*this)(0,0),     0,            0,         (*this)(1,0),       0,           0,         (*this)(2,0),    0,           0,         (*this)(3,0),    0,                   
                    0,       0,            (*this)(0,0),     0,                0,         (*this)(1,0),  0,           0,         (*this)(2,0),    0,           0,         (*this)(3,0),           
                    (*this)(0,1),0,                0,         (*this)(1,1),        0,           0,         (*this)(2,1),    0,           0,       (*this)(3,1),    0,         0,
                    0,       (*this)(0,1),     0,            0,         (*this)(1,1),       0,           0,         (*this)(2,1),    0,           0,         (*this)(3,1),    0,  
                    0,       0,            (*this)(0,1),     0,                0,         (*this)(1,1),  0,           0,         (*this)(2,1),    0,           0,         (*this)(3,1),       
                    (*this)(0,2),0,                0,         (*this)(1,2),        0,           0,         (*this)(2,2),    0,           0,   (*this)(3,2),    0,           0,
                    0,       (*this)(0,2),     0,            0,         (*this)(1,2),       0,           0,         (*this)(2,2),    0,           0,         (*this)(3,2),   0,              
                    0,       0,            (*this)(0,2),     0,                0,         (*this)(1,2),  0,           0,         (*this)(2,2),    0,           0,         (*this)(3,2);            
            return M; 

        }

    protected:

    private:

    };

    //try to do this eigen style so I avoid copying so much data
    //expression A*B
    /*template<class ArgTypeA, class ArgTypeB>
    struct flatten_multiply_helper {

        //flatten to a column vector
        typedef Eigen::Matrix<typename ArgTypeA::Scalar,
                       ArgTypeA::RowsAtCompileTime*ArgTypeB::ColsAtCompileTime,
                       ArgTypeB::RowsAtCompileTime*ArgTypeB::ColsAtCompileTime,
                       Eigen::ColMajor,
                       ArgTypeA::RowsAtCompileTime*ArgTypeB::ColsAtCompileTime,
                       ArgTypeB::RowsAtCompileTime*ArgTypeB::ColsAtCompileTime> MatrixType;

    };

    //access approriate parts of matrix to flatten
    template<class ArgTypeA, class ArgTypeB>
    class flatten_multiply_functor {
        const ArgTypeA &m_flatten;

        public:
            flatten_multiply_functor(const ArgTypeA &arg) : m_to_flatten(arg) { }

            const typename ArgType::Scalar operator()(size_t row, size_t col) const {

                return 0;
            }
    };

    template<class ArgTypeA, class ArgTypeB>
    Eigen::CwiseNullaryOp<flatten_multiply_functor<ArgTypeA, ArgTypeB>,
                          typename flatten_multiply_helper<ArgTypeA, ArgTypeB>::MatrixType>
    flatten_multiply_eigen(const Eigen::MatrixBase<ArgTypeA> &arg) {

        using MatrixType = typename flatten_multiply_helper<ArgTypeA, ArgTypeB>::MatrixType;

        return MatrixType::NullaryExpr(arg.size(), 1, flatten_multiply_functor<ArgTypeA, ArgTypeB>(arg.derived()));
    }*/

}

#ifndef SIM_STATIC_LIBRARY
# include<../src/flatten_multiply.cpp>
#endif

#endif