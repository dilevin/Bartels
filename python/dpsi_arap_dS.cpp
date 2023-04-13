#include <npe.h>

//bartels
#include <dpsi_arap_dS.h>

npe_function(dpsi_arap_dS)
npe_arg(S, dense_float, dense_double)
npe_arg(params, npe_matches(S))
npe_begin_code()

    Eigen::Vector6x<npe_Scalar_S> g; 
    Eigen::Vector6x<npe_Scalar_S> S_in = S;
    sim::dpsi_arap_dS(g, S_in, params);
    return npe::move(g);

npe_end_code()
