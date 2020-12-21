#ifndef SIM_BARTELS_TYPES
#define SIM_BARTELS_TYPES

namespace sim {

    enum SolverExitStatus {
        CONVERGED,
        MAX_ITERATIONS_REACHED
    };

    auto default_optimization_callback = [](auto &x, auto &g, auto &H, SolverExitStatus &searchstatus) {};

}
#endif