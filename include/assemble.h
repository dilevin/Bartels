#ifndef SIM_ASSEMBLE_H
#define SIM_ASSEMBLE_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

//two utility classes - one that gets me the return typeof a function and one that flattens the return type
template<typename Func, typename ...Params, typename DerivedRet, typename DerivedX,  typename DerivedE>
void assemble(Eigen::MatrixBase<DerivedRet> &assembled, 
              Func func, Params ... &&params, 
              Eigen::MatrixBase<DerivedE> &E);

#ifndef SIM_STATIC_LIBRARY
# include<../src/assemble.cpp>
#endif

#endif
