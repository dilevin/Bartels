#ifndef SIM_SIMPLE_PSD_FIX_H
#define SIM_SIMPLE_PSD_FIX_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>

namespace sim {

    template<typename DerivedType, typename Scalar = double>
    void simple_psd_fix(Eigen::MatrixBase<DerivedType> &A, Scalar tol= 1e-6);


}

#ifndef SIM_STATIC_LIBRARY
# include<../src/simple_psd_fix.cpp>
#endif

#endif
