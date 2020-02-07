#ifdef SIM_STATIC_LIBRARY
# include<../include/assemble.h>
#endif

template <typename DerivedV>
inline const auto get_param(const Eigen::DenseBase<DerivedV> &V, unsigned int i) {
    return V.row(i);
}

template <typename DerivedV>
inline const auto & get_param(const std::vector<DerivedV> &V, unsigned int i) {
    return V[i];
}

struct relay_params_struct {
  template <typename Func, typename Ret, typename ...Params>
  inline relay_params_struct(Func &func, Ret &&tmp, const Params & ... params) {
    func(tmp, params ...);
  }
};

template<typename Func, typename Ret, typename ...Params>
inline void relay_params(unsigned int eid, Func &func, Ret && tmp, const Params & ... params) {
  //relay_params_struct{ func, tmp, (params.row(eid))...};
  relay_params_struct{ func, tmp, (get_param(params,eid))...};
}

//assemble over a graph to a vector 
template<typename Func, typename ...Params, typename DerivedRet,  typename DerivedTmp>
void sim::assemble(
                Eigen::SparseMatrix<DerivedRet> &assembled, 
                unsigned int rows, unsigned int cols, 
                Eigen::Ref<const Eigen::MatrixXi> E_from,  
                Eigen::Ref<const Eigen::MatrixXi> E_to,  
                Func func, Eigen::MatrixBase<DerivedTmp> &tmp,
                const Params & ... params) {

    using Scalar = typename DerivedTmp::Scalar;

    //init triplet list
    std::vector<Eigen::Triplet<Scalar>> triplet_list;
    unsigned int block_size_to, block_size_from;

    assembled.resize(rows, cols); 

    //std::cout<<"Rows: "<<assembled.rows()<<" Cols: "<<assembled.cols()<<"\n";

    //std::cout<<"A "<<tmp<<" \n";
    //iterate through element hypergraph
    for(unsigned int ie=0; ie < E_from.rows(); ++ie) {
        
        //std::cout<<"B "<<tmp<<" \n";
        //evaluate func for each hyper edge
        //func(tmp, E_from.row(ie), params...); //run function on element hyper edge 
        relay_params(ie, func,tmp, E_from, params...);
        
        //std::cout<<"B1 \n";
        block_size_to = tmp.rows()/E_to.cols();
        block_size_from = tmp.cols()/E_from.cols(); 
        

        for(unsigned int iblock_to=0; iblock_to <E_to.cols(); ++iblock_to) {
          for(unsigned int iblock_from=0; iblock_from<E_from.cols(); ++iblock_from) {
            
            for(unsigned int iblk_r=0; iblk_r < block_size_to; ++iblk_r) {
              for(unsigned int iblk_c=0; iblk_c < block_size_from; ++iblk_c) {
                 triplet_list.push_back(Eigen::Triplet<Scalar>(block_size_to*E_to(ie, iblock_to) + iblk_r, 
                                                       block_size_from*E_from(ie, iblock_from) + iblk_c,
                                                       tmp(block_size_to*iblock_to+iblk_r, block_size_from*iblock_from+iblk_c)));

              }
            } 
          }
        }
          
    }

    assembled.setFromTriplets(triplet_list.begin(), triplet_list.end());


 }

//assemble over graph to a vector
template<typename Func, typename ...Params, typename DerivedRet,  typename DerivedTmp>
void sim::assemble(Eigen::VectorXx<DerivedRet> &assembled, 
            unsigned int rows, 
            Eigen::Ref<const Eigen::MatrixXi> E_from,  
            Eigen::Ref<const Eigen::MatrixXi> E_to,  
            Func func, Eigen::DenseBase<DerivedTmp> &tmp, 
            const Params & ... params) {

    using Scalar = typename DerivedTmp::Scalar;

    //init triplet list
    unsigned int block_size_to, block_size_from;

    assembled.resize(rows, 1); 
    assembled.setZero();

    //iterate through element hypergraph
    for(unsigned int ie=0; ie < E_from.rows(); ++ie) {
        
        relay_params(ie, func,tmp, E_from, params...);
        
        block_size_to = tmp.rows()/E_to.cols();
        
        for(unsigned int iblock_to=0; iblock_to <E_to.cols(); ++iblock_to) {
            for(unsigned int iblk_r=0; iblk_r < block_size_to; ++iblk_r) {
              
                 assembled(block_size_to*E_to(ie, iblock_to) + iblk_r) += tmp(block_size_to*iblock_to+iblk_r);
            } 
        }
    }


}