#ifdef SIM_STATIC_LIBRARY
# include<../include/fixed_point_constraint_matrix.h>
#endif

#include <assert.h>

template<typename RetType, int Options, typename StorageIndex, typename DerivedV>
void sim::fixed_point_constraint_matrix(Eigen::SparseMatrix<RetType, Options, StorageIndex> &P, const  Eigen::MatrixBase<DerivedV> &V, Eigen::Ref<const Eigen::VectorXi> fixed_indices) {

    using Scalar =  RetType;

    unsigned int num_constraints = fixed_indices.rows();
    unsigned int q_size = V.rows()*V.cols(); 
    unsigned int stride = V.cols();

    std::vector<Eigen::Triplet<Scalar>> triplets;

    P.resize(q_size - stride*num_constraints, q_size); 

    unsigned int jj=0;

    for(unsigned int ii=0; ii<q_size; ii+=stride) {
        
        if(jj < fixed_indices.size() && fixed_indices[jj] == ii/stride) {
            jj += 1;
        } else {
            for(unsigned int kk=0; kk<stride; ++kk) {
                triplets.push_back(Eigen::Triplet<double>(ii-stride*jj +kk ,ii+kk, 1.));
                //triplets.push_back(Eigen::Triplet<double>(ii-stride*jj+1,ii+1, 1.));
                //triplets.push_back(Eigen::Triplet<double>(ii-stride*jj+2,ii+2, 1.));
            }
        }
        
    }

    P.setFromTriplets(triplets.begin(), triplets.end());

}