#ifndef SIM_FLATTEN_MULTIPLY_H
#define SIM_FLATTEN_MULTIPLY_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

#include <iostream>

namespace sim {

    //Given an expression C = A*B, return a matrix A^* s.t
    //X(:) = (A^*)*B(:), here I am using matlab colon operators to denote flattening a matrix
    //try to do this eigen style so I avoid copying so much data
    //expression A*B
    template<class ArgTypeA, class ArgTypeB>
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
    class flatten_multiply_right_functor {
        const ArgTypeB &m_flatten;

        public:
            flatten_multiply_right_functor(const ArgTypeB &arg) : m_flatten(arg) { }

            //for some reason I can only get these to work with linear indexes 
            const typename ArgTypeA::Scalar operator()(size_t index) const {

                using MatrixType = typename flatten_multiply_helper<ArgTypeA, ArgTypeB>::MatrixType;

                constexpr size_t rowsOut = ArgTypeA::RowsAtCompileTime;
                constexpr size_t colsOut = ArgTypeB::ColsAtCompileTime;
                constexpr size_t rowsA = ArgTypeA::RowsAtCompileTime;
                constexpr size_t colsA = ArgTypeA::ColsAtCompileTime;

                size_t size_mult = rowsOut*colsOut;

                size_t lin_A = std::floor(index/size_mult);
                size_t lin_out = std::floor(index%(size_mult));

                //indices for output matrix
                size_t j = std::floor(lin_out/rowsOut);
                size_t i = std::floor(lin_out%rowsOut);

                //indices for A
                size_t m = std::floor(lin_A/rowsA);
                size_t l = std::floor(lin_A%rowsA);

                return (l != i ? 0 : m_flatten(m,j));
            }
    };

    template<class ArgTypeA, class ArgTypeB>
    Eigen::CwiseNullaryOp<flatten_multiply_right_functor<ArgTypeA, ArgTypeB>,
                          typename flatten_multiply_helper<ArgTypeA, ArgTypeB>::MatrixType>
    flatten_multiply_right(const Eigen::MatrixBase<ArgTypeB> &arg) {

        using MatrixType = typename flatten_multiply_helper<ArgTypeA, ArgTypeB>::MatrixType;

        return MatrixType::NullaryExpr(ArgTypeA::RowsAtCompileTime*ArgTypeB::ColsAtCompileTime,
                                       ArgTypeB::RowsAtCompileTime*ArgTypeB::ColsAtCompileTime, 
                                       flatten_multiply_right_functor<ArgTypeA, ArgTypeB>(arg.derived()));
    }


    template<class ArgTypeA, class ArgTypeB>
    class flatten_multiply_functor {
        const ArgTypeA &m_flatten;

        public:
            flatten_multiply_functor(const ArgTypeA &arg) : m_flatten(arg) { }

            //for some reason I can only get these to work with linear indexes 
            const typename ArgTypeA::Scalar operator()(size_t index) const {

                using MatrixType = typename flatten_multiply_helper<ArgTypeA, ArgTypeB>::MatrixType;

                constexpr size_t rowsOut = ArgTypeA::RowsAtCompileTime;
                constexpr size_t colsOut = ArgTypeB::ColsAtCompileTime;
                constexpr size_t rowsB = ArgTypeB::RowsAtCompileTime;
                constexpr size_t colsB = ArgTypeB::ColsAtCompileTime;

                size_t size_mult = rowsOut*colsOut;

                size_t lin_B = std::floor(index/size_mult);
                size_t lin_out = std::floor(index%(size_mult));

                //indices for output matrix
                size_t j = std::floor(lin_out/rowsOut);
                size_t i = std::floor(lin_out%rowsOut);

                //indices for A
                size_t m = std::floor(lin_B/rowsB);
                size_t l = std::floor(lin_B%rowsB);

                return (j != m ? 0 : m_flatten(i,l));
            }
    };

    template<class ArgTypeB, class ArgTypeA>
    Eigen::CwiseNullaryOp<flatten_multiply_functor<ArgTypeA, ArgTypeB>,
                          typename flatten_multiply_helper<ArgTypeA, ArgTypeB>::MatrixType>
    flatten_multiply(const Eigen::MatrixBase<ArgTypeA> &arg) {

        using MatrixType = typename flatten_multiply_helper<ArgTypeA, ArgTypeB>::MatrixType;

        return MatrixType::NullaryExpr(ArgTypeA::RowsAtCompileTime*ArgTypeB::ColsAtCompileTime,
                                       ArgTypeB::RowsAtCompileTime*ArgTypeB::ColsAtCompileTime, 
                                       flatten_multiply_functor<ArgTypeA, ArgTypeB>(arg.derived()));
    }

}

#ifndef SIM_STATIC_LIBRARY
# include<../src/flatten_multiply.cpp>
#endif

#endif