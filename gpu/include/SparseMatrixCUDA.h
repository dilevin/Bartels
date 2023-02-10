#ifndef BARTELS_SPARSEMATRIX_CUDA
#define BARTELS_SPARSEMATRIX_CUDE

#include <EigenTypes.h>
#include <cusparse.h>
#include<cusolverDn.h>

namespace bartels {

    template<typename DataType, typename Storage>
    class SparseMatrixCUDA {

        public:
        private:
        protected:

    };
}

#ifndef SIM_STATIC_LIBRARY
# include<../src/SparseMatrixCUDA.cpp>
#endif

#endif
