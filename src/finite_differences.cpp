#ifdef SIM_STATIC_LIBRARY
# include<../include/finite_differences.h>
#endif

//centered differences
//scalar function to vector
template<class Function, typename DerivedG, typename DerivedX, typename Scalar>
void sim::finite_differences_centered(Eigen::MatrixBase<DerivedG> &grad, Function &f, const Eigen::MatrixBase<DerivedX>  &x, Scalar tol)
{
    if(x.rows() == 0) {
        std::cout<<"ERROR: Provided empty parameters to finite_differences_centered";
        exit(1);
    }

    if(grad.rows() != x.rows()) 
    {
        grad.resize(x.rows(), 1);
    }

    DerivedX tmp_x = x;
   
    //#pragma omp parallel for private(tmp_x)
    for(unsigned int ii=0; ii<x.rows(); ++ii) {
        
        tmp_x(ii) = x(ii) + tol;

        Scalar fp1 = f(tmp_x);

        tmp_x(ii) = x(ii) - tol; 

        grad(ii) = (f(tmp_x) - fp1)/(2.0*tol);

        tmp_x(ii) = x(ii);
    }

}

//vector function to matrix 
template<class Function, typename DerivedH, typename DerivedX, typename Scalar>
void sim::finite_differences_hessian_centered(Eigen::MatrixBase<DerivedH> &H, Function &f, const Eigen::MatrixBase<DerivedX> &x, Scalar tol)
{

    if(x.rows() == 0) {
        std::cout<<"ERROR: Provided empty parameters to finite_differences_hessian_centered";
        exit(1);
    }

    if((H.rows() != x.rows()) || (H.cols() != x.rows())) 
    {
        H.resize(x.rows(), x.rows());
    }

    H.setZero();

    DerivedX tmp_x = x;
    
    //collapse (2) collapses my nested loops
    //#pragma omp parallel for collpase(2) private(tmp_x) 
    {
        for(unsigned int ii=0; ii<x.rows(); ++ii) {
            for(unsigned int jj=0;jj<x.rows(); ++jj) {

                //i+1, j+1
                tmp_x(ii) = x(ii) + tol;
                tmp_x(jj) = x(jj) + tol;
                H(ii,jj) += f(tmp_x);

                //i+1, j-1
                tmp_x(jj) = x(jj) - tol; 
                H(ii,jj) -= f(tmp_x);

                //i-1, j+1
                tmp_x(ii) = x(ii) - tol;
                tmp_x(jj) = x(jj) + tol;
                H(ii,jj) -= f(tmp_x);

                //i-1, j-1
                tmp_x(jj) = x(jj) - tol;
                H(ii,jj) += f(tmp_x);
                H(ii,jj) /= (4.0*tol*tol);

                tmp_x(ii) = x(ii);
                tmp_x(jj) = x(jj);

            }

            //fill in the diagonal with better estimate
            tmp_x(ii) = x(ii) + 2.0*tol;
            H(ii,ii) = -f(tmp_x);

            tmp_x(ii) = x(ii) + tol;
            H(ii,ii) += 16.0*f(tmp_x);

            tmp_x(ii) = x(ii);
            H(ii,ii) -= 30.0*f(tmp_x);

            tmp_x(ii) = x(ii) - tol;
            H(ii,ii) += 16.0*f(tmp_x);

            tmp_x(ii) = x(ii) - 2.0*tol;
            H(ii,ii) -= f(tmp_x);

            H(ii,ii) /= (12.0*tol*tol);
        }

    }




}
