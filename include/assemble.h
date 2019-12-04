#ifndef SIM_ASSEMBLE_H
#define SIM_ASSEMBLE_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

#include <flatten_multiply.h>

namespace sim {

    template<typename Func, typename ...Params, typename DerivedRet, typename DerivedX,  typename DerivedTmp>
    void assemble(Eigen::SparseMatrixBase<DerivedRet> &assembled, 
                Func func, Params ... &&params, 
                Eigen::MatrixBase<DerivedTmp> &tmp);

    template<typename Func, typename ...Params, typename DerivedRet, typename DerivedX,  typename DerivedTmp>
    void assemble(Eigen::SparseMatrixBase<DerivedRet> &assembled, 
                Func func, Params ... &&params, 
                Flatten &tmp);

}

#ifndef SIM_STATIC_LIBRARY
# include<../src/assemble.cpp>
#endif

#endif
