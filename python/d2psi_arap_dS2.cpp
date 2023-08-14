#include <npe.h>

//bartels
#include <d2psi_arap_dS2.h>

npe_function(d2psi_arap_dS2)
npe_arg(S, dense_float, dense_double)
npe_arg(params, npe_matches(S))
npe_begin_code()

    Eigen::Matrix<npe_Scalar_S, 6, 6> H; 
    Eigen::Vector6x<npe_Scalar_S> S_in = S;
    sim::d2psi_arap_dS2(H, S_in, params);
    return npe::move(H);

npe_end_code()