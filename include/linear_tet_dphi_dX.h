#ifndef SIM_LINEAR_TET_DPHI_DX_H
#define SIM_LINEAR_TET_DPHI_DX_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {
    template<typename DerivedP, typename DerivedV, typename DerivedR>
    void linear_tet_dphi_dX(Eigen::DenseBase<DerivedP> &dphi, const Eigen::MatrixBase<DerivedV> &V, 
                            Eigen::Ref<const Eigen::RowVectorXi> element, 
                            Eigen::MatrixBase<DerivedR> const & X);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/linear_tet_dphi_dX.cpp>
#endif

#endif
