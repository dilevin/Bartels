#ifdef SIM_STATIC_LIBRARY
# include<../include/find_max_vertices.h>
#endif

template<typename DerivedV, typename Scalar>
void sim::find_max_vertices(std::vector<int> &indices, const Eigen::DenseBase<DerivedV> &V, unsigned int dim, Scalar tol) {

    Scalar max_vertex = V(0,dim); 
    
    for(unsigned int vi=0; vi<V.rows(); ++vi) {
        max_vertex = (V(vi,dim) > max_vertex ? V(vi,dim) : max_vertex);
    }

    for(unsigned int vi=0; vi<V.rows(); ++vi) {

        if(std::abs(V(vi,dim)-max_vertex) <= tol) {
            indices.push_back(vi);
        }
    }

}
