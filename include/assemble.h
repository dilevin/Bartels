#ifndef SIM_ASSEMBLE_H
#define SIM_ASSEMBLE_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

#include <flatten_multiply.h>

namespace sim {

    //assemble over graph to a sparse matrix
    template<typename Func, typename ...Params, typename DerivedRet,  typename DerivedTmp>
    void assemble(Eigen::SparseMatrix<DerivedRet> &assembled, 
                unsigned int rows, unsigned int cols, 
                Eigen::Ref<Eigen::MatrixXi> E_from,  
                Eigen::Ref<Eigen::MatrixXi> E_to,  
                Func func, Eigen::MatrixBase<DerivedTmp> &tmp, 
                Params && ... params);

    
    template<typename Func, typename ...Params, typename DerivedRet,  typename DerivedTmp>
    void assemble(Eigen::VectorXx<DerivedRet> &assembled, 
            unsigned int rows, 
            Eigen::Ref<Eigen::MatrixXi> E_from,  
            Eigen::Ref<Eigen::MatrixXi> E_to,  
            Func func, Eigen::DenseBase<DerivedTmp> &tmp, 
            Params && ... params);



}

#ifndef SIM_STATIC_LIBRARY
# include<../src/assemble.cpp>
#endif

#endif
