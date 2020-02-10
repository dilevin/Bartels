#ifdef SIM_STATIC_LIBRARY
# include<../include/simple_psd_fix.h>
#endif

template<typename DerivedType, typename Scalar>
void sim::simple_psd_fix(Eigen::MatrixBase<DerivedType> &A, Scalar tol) {

    // hard coded for tet, need to change size for hex
    Eigen::SelfAdjointEigenSolver< Eigen::MatrixXx<typename DerivedType::Scalar> > es(A);
        
    Eigen::MatrixXx<Scalar> diag_eval = es.eigenvalues().real();
    
    for (unsigned int i = 0; i < diag_eval.rows(); ++i) {
        if (diag_eval(i)<tol) {
            diag_eval(i) = tol;
        }
    }
    
    A = es.eigenvectors().real() * diag_eval.asDiagonal() * es.eigenvectors().real().transpose();
    
}