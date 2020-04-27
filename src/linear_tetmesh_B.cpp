#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_B.h>
#endif

template<typename DerivedRet, int Options, typename StorageIndex, typename DerivedV>
void sim::linear_tetmesh_B(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &B, Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E) {

    
    Eigen::MatrixXd dX;
    linear_tetmesh_dphi_dX(dX, V,  E);

    auto assemble_func = [](auto &dX, auto &e, auto &dX_dense) { 
        dX = sim::flatten_multiply_right<Eigen::Matrix<DerivedRet, 3,4> >(
                sim::unflatten<4,3>(dX_dense));
    };
                    
    
    Eigen::MatrixXi E_out;
    E_out.resize(E.rows(), 1);

    for(unsigned int ii=0; ii<E_out.rows(); ++ii) {
        E_out(ii,0) = ii;
    }

    //index set for rows of matrix is 
    Eigen::Matrix<DerivedRet,9,12> dXtmp;
    sim::assemble(B, E.rows()*V.cols()*3, V.cols()*V.rows(), E,E_out, assemble_func, dXtmp, dX);
    
}

