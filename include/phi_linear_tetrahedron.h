#ifndef SIM_PHI_LINEAR_TETRAHEDRON_H
#define SIM_PHI_LINEAR_TETRAHEDRON_H

#include <Eigen/Dense>
#include <EigenTypes.h>

template<typename DataType>
template<typename DataType, typename DerivedV>
void phi_linear_tetrahedron(Eigen::Vector4x<DataType> &phi, 
                            const Eigen::DenseBase<DerivedV> &V, 
                            const Eigen::DenseBase<Eigen::RowVectorXx<DataType> >  &e, 
                            const Eigen::DenseBase<Eigen::Vector3x<DataType> > &x);

#ifndef SIM_STATIC_LIBRARY
#   include <../src/phi_linear_tetrahedron.cpp>
#endif

#endif
