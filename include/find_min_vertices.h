
#ifndef SIM_FIND_MIN_VERTICES_H
#define SIM_FIND_MIN_VERTICES_H

#include <EigenTypes.h>
#include <vector>

namespace sim {
    
    template<typename DerivedV, typename Scalar>
    void find_min_vertices(std::vector<int> &indices, const Eigen::DenseBase<DerivedV> &V, unsigned int dim, Scalar tol = 1e-3);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/find_min_vertices.cpp>
#endif

#endif