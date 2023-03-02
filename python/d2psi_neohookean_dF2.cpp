#include <npe.h>

//bartels
#include <BlockDiagonalMatrix.h>
#include <d2psi_neohookean_dF2.h>

npe_function(d2psi_neohookean_dF2)
npe_arg(F, dense_float, dense_double)
npe_arg(E, dense_int)
npe_arg(params, npe_matches(F))
npe_begin_code()

    Eigen::BlockDiagonal<npe_Scalar_F, Eigen::Dynamic> H;
    H.resize(E.rows(), 9); 
    
    #pragma omp parallel
    {
        
        Eigen::Matrix<npe_Scalar_F,9,9> Hele;
    
        #pragma omp for schedule(static)
        for(unsigned int ii=0; ii<E.rows(); ++ii) {
            sim::d2psi_neohookean_dF2(Hele, sim::unflatten<3,3>(F.row(ii)), params.row(ii)); 
            H.diagonalBlock(ii) = Hele;
        }
        
    }

    return std::make_tuple(npe::move(H));

npe_end_code()

