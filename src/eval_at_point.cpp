#ifdef SIM_STATIC_LIBRARY
# include<../include/eval_at_point.h>
#endif

#include <assert.h>

template<typename DerivedRet, typename DerivedV, 
         int Rows, int Cols, int Options, int MaxRows, int MaxCols,
         typename Func2, typename DerivedX>
void sim::eval_at_point(Eigen::MatrixXx<DerivedRet> &results, const Eigen::MatrixBase<DerivedV> &V, Eigen::Ref<const Eigen::MatrixXi> E, 
                        Func2 func, Eigen::Matrix<DerivedRet, Rows, Cols, Options, MaxRows, MaxCols> tmp, 
                        const Eigen::MatrixBase<DerivedX> &X) {

    assert(E.rows() == X.rows());

    results.resize(E.rows(), flatten(tmp).rows());

    for(unsigned int ie=0; ie< E.rows(); ++ie) {
        func(tmp, V, E.row(ie), X.row(ie));
        results.row(ie) = flatten(tmp).transpose();
    }

}