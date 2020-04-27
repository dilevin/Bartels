#ifdef SIM_STATIC_LIBRARY
# include<../include/rigid_inertia_com.h>
#endif

#include <cassert>

//compute inertia matrix and volume by integrating on surfaces
template<typename ReturnType, typename DerivedV>
void sim::rigid_inertia_com(Eigen::Matrix3x<ReturnType> &I, Eigen::Vector3x<ReturnType> & center, ReturnType &mass, 
                           const Eigen::MatrixBase<DerivedV> &V, Eigen::Ref<const Eigen::MatrixXi> F, const ReturnType &density) {

    constexpr double oneDiv6{ 1.0 / 6.0 };
    constexpr double oneDiv24{ 1.0 / 24.0 };
    constexpr double oneDiv60{ 1.0 / 60.0 };
    constexpr double oneDiv120{ 1.0 / 120.0 };
    
    // order:  1, x, y, z, x^2, y^2, z^2, xy, yz, zx
    Eigen::VectorXd integral = Eigen::VectorXd::Zero(10);
    
    for( int i = 0; i < F.rows(); ++i )
    {
        // Copy the vertices of triangle i
        const Eigen::Vector3d v0{ V.row( F( i, 0 ) ) };
        const Eigen::Vector3d v1{ V.row( F( i, 1 ) ) };
        const Eigen::Vector3d v2{ V.row( F( i, 2 ) ) };
        
        // Compute a normal for the current triangle
        const Eigen::Vector3d N{ ( v1 - v0 ).cross( v2 - v0 ) };
        
        // Compute the integral terms
        double tmp0{ v0.x() + v1.x() };
        double tmp1{ v0.x() * v0.x() };
        double tmp2{ tmp1 + v1.x() * tmp0 };
        const double f1x{ tmp0 + v2.x() };
        const double f2x{ tmp2 + v2.x() * f1x };
        const double f3x{ v0.x() * tmp1 + v1.x() * tmp2 + v2.x() * f2x };
        const double g0x{ f2x + v0.x() * ( f1x + v0.x() ) };
        const double g1x{ f2x + v1.x() * ( f1x + v1.x() ) };
        const double g2x{ f2x + v2.x() * ( f1x + v2.x() ) };
        
        tmp0 = v0.y() + v1.y();
        tmp1 = v0.y() * v0.y();
        tmp2 = tmp1 + v1.y() * tmp0;
        const double f1y{ tmp0 + v2.y() };
        const double f2y{ tmp2 + v2.y() * f1y };
        const double f3y{ v0.y() * tmp1 + v1.y() * tmp2 + v2.y() * f2y };
        const double g0y{ f2y + v0.y() * ( f1y + v0.y() ) };
        const double g1y{ f2y + v1.y() * ( f1y + v1.y() ) };
        const double g2y{ f2y + v2.y() * ( f1y + v2.y() ) };
        
        tmp0 = v0.z() + v1.z();
        tmp1 = v0.z()*v0.z();
        tmp2 = tmp1 + v1.z()*tmp0;
        const double f1z{ tmp0 + v2.z() };
        const double f2z{ tmp2 + v2.z() * f1z };
        const double f3z{ v0.z() * tmp1 + v1.z() * tmp2 + v2.z() * f2z };
        const double g0z{ f2z + v0.z() * ( f1z + v0.z() ) };
        const double g1z{ f2z + v1.z() * ( f1z + v1.z() ) };
        const double g2z{ f2z + v2.z() * ( f1z + v2.z() ) };
        
        // Update integrals
        integral(0) += N.x() * f1x;
        integral(1) += N.x() * f2x;
        integral(2) += N.y() * f2y;
        integral(3) += N.z() * f2z;
        integral(4) += N.x() * f3x;
        integral(5) += N.y() * f3y;
        integral(6) += N.z() * f3z;
        integral(7) += N.x() * ( v0.y() * g0x + v1.y() * g1x + v2.y() * g2x );
        integral(8) += N.y() * ( v0.z() * g0y + v1.z() * g1y + v2.z() * g2y );
        integral(9) += N.z() * ( v0.x() * g0z + v1.x() * g1z + v2.x() * g2z );
    }
    
    integral(0) *= oneDiv6;
    integral(1) *= oneDiv24;
    integral(2) *= oneDiv24;
    integral(3) *= oneDiv24;
    integral(4) *= oneDiv60;
    integral(5) *= oneDiv60;
    integral(6) *= oneDiv60;
    integral(7) *= oneDiv120;
    integral(8) *= oneDiv120;
    integral(9) *= oneDiv120;
    
    // Mass
    mass = integral(0);
    
    // Center of mass
    center = Eigen::Vector3d{ integral(1), integral(2), integral(3) } / mass;
    
    // Inertia relative to world origin
    Eigen::Matrix3d R;

    R(0,0) = integral(5) + integral(6);
    R(0,1) = -integral(7);
    R(0,2) = -integral(9);
    R(1,0) = R(0,1);
    R(1,1) = integral(4) + integral(6);
    R(1,2) = -integral(8);
    R(2,0) = R(0,2);
    R(2,1) = R(1,2);
    R(2,2) = integral(4) + integral(5);
    
    // Comptue the inertia relative to the center of mass
    R(0,0) -= mass * (center.y() * center.y() + center.z() * center.z() );
    R(0,1) += mass * center.x() * center.y();
    R(0,2) += mass * center.z() * center.x();
    R(1,0) = R(0,1);
    R(1,1) -= mass * ( center.z() * center.z() + center.x() * center.x() );
    R(1,2) += mass * center.y() * center.z();
    R(2,0) = R(0,2);
    R(2,1) = R(1,2);
    R(2,2) -= mass * ( center.x() * center.x() + center.y() * center.y() );
    
    I = R;
    
    // All inertias should be positive
    // Check that we have an orthonormal transformation
    //assert( ( R * R.transpose() - Eigen::Matrix3d::Identity() ).template lpNorm<Eigen::Infinity>() <= 1.0e-9 );
   // assert( fabs( R.determinant() - 1.0 ) <= 1.0e-9 );

}