#ifndef SIM_RELAY_PARAMS_H
#define SIM_RELAY_PARAMS_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <EigenTypes.h>


namespace sim {

    template <typename DerivedV>
    inline const auto get_param(const  Eigen::MatrixBase<DerivedV> &V, unsigned int i) {
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


    template<typename Func, typename ...Params>
    inline auto relay_params_return(unsigned int eid, Func &func, const Params & ... params) {
    //relay_params_struct{ func, tmp, (params.row(eid))...};
    return func((get_param(params,eid))...);
    }

}

#ifndef SIM_STATIC_LIBRARY
# include<../src/relay_params.cpp>
#endif

#endif
