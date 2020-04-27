#ifndef IGL_MATLAB_PREPARE_LHS_EXTRA_H
#define IGL_MATLAB_PREPARE_LHS_EXTRA_H
#include <igl/igl_inline.h>
#include <igl/matlab/prepare_lhs.h>
#include <mex.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>
namespace igl
{
  namespace matlab
  {
    // SparseMatrix Row Ordering
    template <typename Vtype>
    void prepare_lhs_double(
      const Eigen::SparseMatrix<Vtype, Eigen::RowMajor> & V,
      mxArray *plhs[]);
  };
}

#ifndef IGL_STATIC_LIBRARY
#  include "prepare_lhs_extra.cpp"
#endif
#endif

