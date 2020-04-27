#ifndef SIM_ASSEMBLE_H
#define SIM_ASSEMBLE_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

#include <flatten_multiply.h>

namespace sim {

    //assemble over graph to a sparse matrix
    template<typename Func, typename ...Params, typename DerivedRet,  int Options, typename StorageIndex, typename DerivedTmp>
    void assemble(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &assembled, 
                unsigned int rows, unsigned int cols, 
                Eigen::Ref<const Eigen::MatrixXi> E_from,  
                Eigen::Ref<const Eigen::MatrixXi> E_to,  
                Func func, Eigen::MatrixBase<DerivedTmp> &tmp, 
                const Params & ... params);

    
    template<typename Func, typename ...Params, typename DerivedRet,  typename DerivedTmp>
    void assemble(Eigen::VectorXx<DerivedRet> &assembled, 
            unsigned int rows, 
            Eigen::Ref<const Eigen::MatrixXi> E_from,  
            Eigen::Ref<const Eigen::MatrixXi> E_to,  
            Func func, Eigen::DenseBase<DerivedTmp> &tmp, 
            const Params & ... params);

    template<typename Func, typename ...Params>
    auto assemble(Eigen::Ref<const Eigen::MatrixXi> E_from,  
                  Func func, 
                  const Params & ... params);



}

#ifndef SIM_STATIC_LIBRARY
# include<../src/assemble.cpp>
#endif

#endif
