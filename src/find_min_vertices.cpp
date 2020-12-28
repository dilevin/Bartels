#ifdef SIM_STATIC_LIBRARY
# include<../include/find_min_vertices.h>
#endif

template<typename DerivedV, typename Scalar>
void sim::find_min_vertices(std::vector<int> &indices, const Eigen::DenseBase<DerivedV> &V, Scalar tol) {

    Scalar min_vertex = V(0,1); 
    
    for(unsigned int vi=0; vi<V.rows(); ++vi) {
        min_vertex = (V(vi,1) < min_vertex ? V(vi,1) : min_vertex);
    }

    for(unsigned int vi=0; vi<V.rows(); ++vi) {

        if(std::abs(V(vi,1)-min_vertex) <= tol) {
            indices.push_back(vi);
        }
    }

}
