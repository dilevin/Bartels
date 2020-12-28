
#ifndef SIM_FIND_MAX_VERTICES_H
#define SIM_FIND_MAX_VERTICES_H

#include <EigenTypes.h>
#include <vector>

namespace sim {
    
    template<typename DerivedV, typename Scalar>
    void find_max_vertices(std::vector<int> &indices, const Eigen::DenseBase<DerivedV> &V, unsigned int dim, Scalar tol = 1e-3);

}

#ifndef SIM_STATIC_LIBRARY
#   include <../src/find_max_vertices.cpp>
#endif

#endif
