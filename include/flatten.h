#ifndef SIM_FLATTEN_H
#define SIM_FLATTEN_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

#include <iostream>

//flatten and unflatten datatypes consistently 
//flatten matrices to vectors in column-major fashion
//i.e A = flatten([u v w]) -> [u;v;w]

namespace sim {

    /*template<typename Scalar, int Rows, int Cols>
    inline auto flatten(Eigen::Matrix<Scalar, Rows, Cols> &&A) {
        return flatten(A);
    }

    template<typename Scalar, int Rows, int Cols>
    inline auto flatten(Eigen::Matrix<Scalar, Rows, Cols> &A) {

        return Eigen::Map<Eigen::Matrix<Scalar, Rows*Cols, 1> >(A.data(), A.size()); 
    }

    
    //unflatten back to indicated matrix type
    template<int RowsOut, int ColsOut, typename Derived>
    inline auto unflatten(Eigen::MatrixBase<Derived> &a) {

        
        //std::cout<<a<<"\n";
        using Scalar = typename Derived::Scalar;
        constexpr int Rows = Derived::RowsAtCompileTime;
        constexpr int Cols = Derived::ColsAtCompileTime;

        return Eigen::Map<Eigen::Matrix<Scalar, RowsOut, ColsOut> >((Eigen::Ref<Eigen::Matrix<Scalar, Rows, Cols> >(a)).data());
    }

    template<int RowsOut, int ColsOut, typename Derived>
    inline auto unflatten(Eigen::MatrixBase<Derived> &&a) {
        return unflatten<RowsOut, ColsOut>(a);
    }

    //alternate unflatten that works on block operations
    template<int RowsOut, int ColsOut, typename DerivedIn>
    inline auto unflatten_row(const Eigen::MatrixBase<DerivedIn> &in) {
        Eigen::Matrix<typename DerivedIn::Scalar, RowsOut, ColsOut> tmp;

        for(unsigned int jj=0; jj<ColsOut; ++jj)
            for(unsigned int ii=0; ii<RowsOut; ++ii) {
                tmp(ii,jj) = in(jj*RowsOut+ii);
            }

        return tmp;
    }*/

    //try to do this eigen style so I avoid copying so much data
    template<class ArgType>
    struct flatten_helper {

        //flatten to a column vector
        typedef Eigen::Matrix<typename ArgType::Scalar,
                       ArgType::RowsAtCompileTime*ArgType::ColsAtCompileTime,
                       1,
                       Eigen::ColMajor,
                       ArgType::RowsAtCompileTime*ArgType::ColsAtCompileTime,
                       1> MatrixType;

    };

    //try to do this eigen style so I avoid copying so much data
    template<int RowTo, int ColTo, class ArgType>
    struct unflatten_helper {

        //flatten to a column vector
        typedef Eigen::Matrix<typename ArgType::Scalar,
                       RowTo,
                       ColTo,
                       Eigen::ColMajor,
                       RowTo,
                       ColTo> MatrixType;

    };

    //access approriate parts of matrix to flatten
    template<class ArgType>
    class flatten_functor {
        const ArgType &m_to_flatten;

        public:
            flatten_functor(const ArgType &arg) : m_to_flatten(arg) { }

            const typename ArgType::Scalar operator()(size_t row, size_t col = 0) const {

                size_t col_from =  std::floor(row/m_to_flatten.rows());
                size_t row_from =  row%m_to_flatten.rows(); 

                return m_to_flatten(row_from, col_from);
            }
    };

    template<int RowTo, int ColTo, class ArgType>
    class unflatten_functor {
        const ArgType &m_unflatten;

        public:
            unflatten_functor(const ArgType &arg) : m_unflatten(arg) { }

            const typename ArgType::Scalar operator()(size_t index) const {
                
                return m_unflatten(index);
            }

            const typename ArgType::Scalar operator()(size_t row, size_t col) const {
                
                return m_unflatten(col*RowTo + row);
            }

    };

    template<class ArgType>
    Eigen::CwiseNullaryOp<flatten_functor<ArgType>,
                          typename flatten_helper<ArgType>::MatrixType>
    flatten(const Eigen::MatrixBase<ArgType> &arg) {

        using MatrixType = typename flatten_helper<ArgType>::MatrixType;

        return MatrixType::NullaryExpr(arg.size(), 1, flatten_functor<ArgType>(arg.derived()));
    }

    //arg type is the flatten from
    template<int RowTo, int ColTo, class ArgType>
    Eigen::CwiseNullaryOp<unflatten_functor<RowTo, ColTo, ArgType>, 
                          typename unflatten_helper<RowTo, ColTo, ArgType>::MatrixType>
    unflatten(const Eigen::MatrixBase<ArgType> &arg) {
        using MatrixType = typename unflatten_helper<RowTo, ColTo, ArgType>::MatrixType;

        return MatrixType::NullaryExpr(RowTo, ColTo, unflatten_functor<RowTo, ColTo, ArgType>(arg.derived()));
    }
}
#endif