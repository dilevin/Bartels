 
#ifdef SIM_STATIC_LIBRARY
#include<../include/linear_tri2d_mass_matrix.h>
#endif

#include <iostream>

template<typename MassMatrixType, typename  Scalar>
void sim::linear_tri2d_mass_matrix(Eigen::DenseBase<MassMatrixType> &M, Eigen::Ref<const Eigen::RowVectorXi> element, Scalar density, Scalar volume) {
     
    Scalar mass = density*volume;

    Scalar c0 = (1.0/6.0)*mass;
    Scalar c1 = (1.0/12.0)*mass;

    //setup the mass matrix
    //m_massMatrix
    //Point Indices
    unsigned int p0 = 0;
    unsigned int p1 = 2;
    unsigned int p2 = 4;

    //Assemble these bad boys //really big 4x4 block matrix
    M.block(p0,p0, 2,2) = c0*Eigen::Matrix<Scalar,2,2>::Identity();
    M.block(p0,p1, 2,2) = c1*Eigen::Matrix<Scalar,2,2>::Identity();
    M.block(p0,p2, 2,2) = c1*Eigen::Matrix<Scalar,2,2>::Identity();

    M.block(p1,p0, 2,2) = c1*Eigen::Matrix<Scalar,2,2>::Identity();
    M.block(p1,p1, 2,2) = c0*Eigen::Matrix<Scalar,2,2>::Identity();
    M.block(p1,p2, 2,2) = c1*Eigen::Matrix<Scalar,2,2>::Identity();

    M.block(p2,p0, 2,2) = c1*Eigen::Matrix<Scalar,2,2>::Identity();
    M.block(p2,p1, 2,2) = c1*Eigen::Matrix<Scalar,2,2>::Identity();
    M.block(p2,p2, 2,2) = c0*Eigen::Matrix<Scalar,2,2>::Identity();

 }