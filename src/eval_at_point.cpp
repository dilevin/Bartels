#ifdef SIM_STATIC_LIBRARY
# include<../include/eval_at_point.h>
#endif

#include <assert.h>

template<typename DerivedRet, typename Scalar, int Rows, int Cols, typename Func2, typename DerivedV>
void sim::eval_at_point(Eigen::MatrixXx<DerivedRet> &results, const Eigen::MatrixXd &V, Eigen::Ref<const Eigen::MatrixXi> E, 
                        Func2 func, Eigen::Matrix<Scalar, Rows, Cols> tmp, const Eigen::MatrixBase<DerivedV> &X) {

    assert(E.rows() == X.rows());

    results.resize(E.rows(), flatten(tmp).rows());

    for(unsigned int ie=0; ie< E.rows(); ++ie) {
        func(tmp, V, E.row(ie), X.row(ie));
        results.row(ie) = flatten(tmp).transpose();
    }

}