#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tri2dmesh_B.h>
#endif

template<typename DerivedRet, int Options, typename StorageIndex, typename DerivedV>
void sim::linear_tri2dmesh_B(Eigen::SparseMatrix<DerivedRet, Options, StorageIndex> &B, const Eigen::MatrixBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E) {
    
    Eigen::MatrixXd dX;
    linear_tri2dmesh_dphi_dX(dX, V,  E);
 
    auto assemble_func = [](auto &dX, auto &e, auto &dX_dense) { 

        Eigen::Matrix3x<DerivedRet> F = Eigen::Matrix3x<DerivedRet>::Zero();  
    
        Eigen::Matrix<DerivedRet, 9,6> P; 
        P<<1, 0, 0, 0, 0, 0, 
            0, 1, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 
            0, 0, 1, 0, 0, 0, 
            0, 0, 0, 1, 0, 0, 
            0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 1, 0, 
            0, 0, 0, 0, 0, 1, 
            0, 0, 0, 0, 0, 0; 
        
        F.block(0,0,3,2) = sim::unflatten<3,2>(dX_dense); 
        
        dX = sim::flatten_multiply_right<Eigen::Matrix<DerivedRet, 3,3> >(F)*P;
    };
                    
    
    Eigen::MatrixXi E_out;
    E_out.resize(E.rows(), 1);

    for(unsigned int ii=0; ii<E_out.rows(); ++ii) {
        E_out(ii,0) = ii;
    }

    //index set for rows of matrix is 
    Eigen::Matrix<DerivedRet,9,6> dXtmp;
    sim::assemble(B, E.rows()*9, V.cols()*V.rows(), E,E_out, assemble_func, dXtmp, dX);
    
}

