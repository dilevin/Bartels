#ifndef SIM_RIGID_INERTIA_COM_H
#define SIM_RIGID_INERTIA_COM_H

#include <Eigen/Dense>
#include <EigenTypes.h>

namespace sim {

    template<typename ReturnType, typename DerivedV>
    void rigid_inertia_com(Eigen::Matrix3x<ReturnType> &I, Eigen::Vector3x<ReturnType> & center, ReturnType &mass, 
                           const Eigen::MatrixBase<DerivedV> &V, Eigen::Ref<const Eigen::MatrixXi> F, const ReturnType &density);
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/rigid_inertia_com.cpp>
#endif

#endif