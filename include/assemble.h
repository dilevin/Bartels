#ifndef SIM_ASSEMBLE_H
#define SIM_ASSEMBLE_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

#include <flatten_multiply.h>

namespace sim {

    //assemble over graph to a vector
    template<typename Func, typename ...Params, typename DerivedRet,  typename DerivedTmp>
    void assemble(Eigen::SparseMatrix<DerivedRet> &assembled, 
                unsigned int rows, unsigned int cols, 
                Eigen::Ref<Eigen::MatrixXi> E_from,  
                Eigen::Ref<Eigen::MatrixXi> E_to,  
                Func func, Eigen::MatrixBase<DerivedTmp> &tmp, 
                Params && ... params);

    //assemble over graph to sparse matrix
    template<typename Func, typename ...Params, typename DerivedRet,  typename DerivedTmp>
    void assemble(Eigen::SparseMatrixBase<DerivedRet> &assembled, 
                  Eigen::Ref<Eigen::MatrixXi> E, 
                  Func func, Params &&... params, 
                  Eigen::MatrixBase<DerivedTmp> &tmp);

    //assemble to sparse matrix using a flatten operator
    template<typename Func, typename ...Params, typename DerivedRet,  typename DerivedTmpA, typename DerivedTmpB>
    void assemble(Eigen::SparseMatrixBase<DerivedRet> &assembled, 
                  Eigen::Ref<Eigen::MatrixXi> E,  
                  Func func, Params &&... params, 
                  Flatten_Multiply<DerivedTmpA, DerivedTmpB> &tmp);

    //TODO: assemble to dense matrix 

}

#ifndef SIM_STATIC_LIBRARY
# include<../src/assemble.cpp>
#endif

#endif
