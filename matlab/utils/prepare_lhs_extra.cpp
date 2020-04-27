
#include "prepare_lhs_extra.h"
#include <algorithm>

template <typename Vtype>
IGL_INLINE void igl::matlab::prepare_lhs_double(
  const Eigen::SparseMatrix<Vtype, Eigen::RowMajor> & M,
  mxArray *plhs[])
{
    using namespace std;
    unsigned int nnz = M.nonZeros();
    
    plhs[0] = mxCreateSparse(M.rows(), M.cols(), nnz, mxREAL);
    
    double *pr = mxGetPr(plhs[0]);
    mwIndex *ir=mxGetIr(plhs[0]);
    mwIndex *jc = mxGetJc(plhs[0]);
    
    mwIndex *w = new mwIndex[M.cols()+1];
    memset(w, 0, sizeof(mwIndex)*(M.cols()+1));
    
    for(unsigned int ii=0; ii<nnz; ++ii) {
        w[M.innerIndexPtr()[ii]+1]++;
    }
    
    for(unsigned int ii=0; ii<M.cols(); ++ii) {
        w[ii+1] = w[ii]+w[ii+1];
        jc[ii+1] = w[ii+1];
    }
    
    jc[0] = 0;
    
    mwIndex q = 0;
    
    for(unsigned int jj=0; jj<M.rows(); ++jj) {
        
        for(unsigned int pp = M.outerIndexPtr()[jj]; pp < M.outerIndexPtr()[jj+1]; ++pp) {
           
            q = w[M.innerIndexPtr()[pp]]++;
            ir[q] = jj;
            pr[q] = M.valuePtr()[pp];
        }
    }
}