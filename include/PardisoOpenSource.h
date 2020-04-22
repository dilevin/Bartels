//Support for using Open Soure Pardiso solver with Eigen 
//Folloewing the structure of MKL PardisoSupport.h
//Eigen style naming of functions
#ifndef EIGEN_PARDISOOPENSOURCE_H
#define EIGEN_PARDISOOPENSOURCE_H

#include <EigenTypes.h>

#ifdef BARTELS_USE_PARDISO

#include <pardiso_os.h>


#include <cstdio>
#include <cstdlib>
#include <cmath>

namespace Eigen {

    template<typename _MatrixType> class PardisoLU;

    namespace internal {

        //traits class to keep track of important values
        template<typename Derived>
        struct pardiso_traits;

        template<typename _MatrixType>
        struct pardiso_traits< PardisoLU<_MatrixType> >
        {
            typedef _MatrixType MatrixType;
            typedef typename _MatrixType::Scalar Scalar;
            typedef typename _MatrixType::RealScalar RealScalar;
            typedef typename _MatrixType::Index Index;

        };
    }

    //pardiso solver base class
    template<class Derived>
    class PardisoImpl
    {
        
        typedef internal::pardiso_traits<Derived> Traits;
    
    public:
        
        typedef typename Traits::MatrixType MatrixType;
        typedef typename Traits::Scalar Scalar;
        typedef typename Traits::RealScalar RealScalar;
        typedef typename Traits::Index Index;
    
        //where we store pardiso data
        typedef Matrix<Scalar,Dynamic,1> VectorType; 
        typedef Matrix<Index, 1, MatrixType::ColsAtCompileTime> IntRowVectorType;
        typedef Matrix<Index, MatrixType::RowsAtCompileTime, 1> IntColVectorType;
        typedef Array<Index,64,1,DontAlign> IntParameterType;
        typedef Array<double,64,1,DontAlign> DoubleParameterType;
        
        enum {
            ScalarIsComplex = NumTraits<Scalar>::IsComplex,
            Flags = internal::traits<MatrixType>::Flags,
            IsRowMajor = Flags&RowMajorBit ? 1 : 0
        };

        //Do all the generic pardiso stuff
        PardisoImpl(unsigned int num_processors = 1) : m_pardiso()
        {
            //eigen_assert((sizeof(Index) >= sizeof(_INTEGER_t) && sizeof(Index) <= 8) && "Non-supported index type");
            
            
            m_integer_params.setZero();
            m_double_params.setZero();
            m_display_stats =0; //no display
            //Number of Processors
            m_num_processors = num_processors;
            m_maxfct = 1; //perform at most one factorization
            m_mnum = 1; // use factorization 1
            
            m_initialized = false; 
            m_IsRowMajor = -1;

            m_analysisIsOk = false;
            m_factorizationIsOk = false;
            

        }

        ~PardisoImpl()
        {
            pardisoRelease();
        }

        inline Index cols() const { return m_n; }
        inline Index rows() const { return m_n; }
    
        /** \brief Reports whether previous computation was successful.
         *
         * \returns \c Success if computation was succesful,
         *          \c NumericalIssue if the matrix appears to be negative.
         */
        ComputationInfo info() const
        {
            eigen_assert(m_initialized && "Decomposition is not initialized.");
            return m_info;
        }

        /** Performs a symbolic decomposition on the sparcity of \a matrix.
         *
         * This function is particularly useful when solving for several problems having the same structure.
         * 
         * \sa factorize()
         */
        Derived& analyzePattern(const MatrixType& matrix);
        
        /** Performs a numeric decomposition of \a matrix
         *
         * The given matrix must has the same sparcity than the matrix on which the symbolic decomposition has been performed.
         *
         * \sa analyzePattern()
         */
        Derived& factorize(const MatrixType& matrix);

        Derived& compute(const MatrixType& matrix, Index nrhs = 1);
        
        /** \returns the solution x of \f$ A x = b \f$ using the current decomposition of A.
         *
         * \sa compute()
         */
        template<typename Rhs>
        inline const internal::solve_retval<PardisoImpl, Rhs>
        solve(const MatrixBase<Rhs>& b) const
        {
            eigen_assert(m_factorizationIsOk);
            eigen_assert(m_initialized && "Pardiso solver is not initialized.");
            eigen_assert(rows()==b.rows()
                        && "PardisoImpl::solve(): invalid number of rows of the right hand side matrix b");
            return internal::solve_retval<PardisoImpl, Rhs>(*this, b.derived());
        }

        Derived& derived()
        {
            return *static_cast<Derived*>(this);
        }
        const Derived& derived() const
        {
            return *static_cast<const Derived*>(this);
        }

        template<typename BDerived, typename XDerived>
        bool _solve(const MatrixBase<BDerived> &b, MatrixBase<XDerived>& x) const;

        /** \warning for advanced usage only.
         * \returns a reference to the parameter array controlling PARDISO.
         * See the PARDISO manual to know how to use it. */
        IntParameterType& pardisoParameterArray()
        {
            return m_integer_params;
        }

    protected:
        void pardisoRelease()
        {
            double   ddum = 0.;              /* Double dummy */
            int      idum = 0;              /* Integer dummy. */
            int error = 0;
            int phase = -1;

            if(m_initialized) {
                m_pardiso.command(m_ptr, &m_maxfct, &m_mnum, &m_matrix_type, &phase, &m_n, m_a.data(), m_outer_array.data(),
                        m_inner_array.data(), &idum, &m_nrhs, m_integer_params.data(), &m_display_stats, &ddum, &ddum, &error, m_double_params.data());

                assert(error ==0);
            }

        }

        bool pardisoInit(int matrix_type)
        {
            m_matrix_type = matrix_type;
            
            bool symmetric = std::abs(m_type) < 10;

            m_integer_params.setZero();
            m_double_params.setZero();
            m_integer_params[0] = 1;   // No solver default
            m_integer_params[1] = 2;   // Use Metis
            m_integer_params[2] = m_num_processors;   // Number of processors
            m_integer_params[3] = 0;   // No iterative-direct algorithm
            m_integer_params[4] = 0;   // No user fill-in reducing permutation
            m_integer_params[5] = 0;   // Write solution into x, b is left unchanged
            m_integer_params[6] = 0;   // Not in use
            m_integer_params[7] = 2;   // Max numbers of iterative refinement steps
            m_integer_params[8] = 0;   // Not in use
            m_integer_params[9] = 13;  // Perturb the pivot elements with 1E-13
            m_integer_params[10] = symmetric ? 0 : 1; // Use nonsymmetric permutation and scaling MPS
            m_integer_params[11] = IsRowMajor ? 0 : 1;  // solve with transpose,  flip this to 1 for column order matrices
            m_integer_params[12] = symmetric ? 0 : 1;  // Maximum weighted matching algorithm is switched-off (default for symmetric).
                                                // Try m_iparm[12] = 1 in case of inappropriate accuracy
            m_integer_params[13] = 0;  // Output: Number of perturbed pivots
            m_integer_params[14] = 0;  // Not in use
            m_integer_params[15] = 0;  // Not in use
            m_integer_params[16] = 0;  // Not in use
            m_integer_params[17] = -1; // Output: Number of nonzeros in the factor LU
            m_integer_params[18] = -1; // Output: Mflops for LU factorization
            m_integer_params[19] = 0;  // Output: Numbers of CG Iterations
            
            m_integer_params[20] = symmetric ? 0 : 1;  //  pivoting
            m_integer_params[26] = 0;  // No matrix checker
            m_integer_params[27] = 0; //(sizeof(RealScalar) == 4) ? 1 : 0;
            m_integer_params[34] = 0;  // C indexing
            m_integer_params[36] = 0;  // CSR
            m_integer_params[49] = 0;  // 0 - In-Core ; 1 - Automatic switch between In-Core and Out-of-Core modes ; 2 - Out-of-Core
            
            memset(m_ptr, 0, sizeof(m_ptr));

            //Initialize Pardiso and check for errors
            int error = 0;
            int solver = 0; /* use sparse direct solver */

            m_pardiso.init(m_ptr,  &m_matrix_type, &solver, m_integer_params.data(), m_double_params.data(), &error);
            
            if (error != 0)
            {
                if (error == -10 )
                    printf("No license file found \n");
                if (error == -11 )
                    printf("License is expired \n");
                if (error == -12 )
                    printf("Wrong username or hostname \n");
                
                return false;
            }
            else {
                printf("[PARDISO]: License check was successful ... \n");
                return true;
            }

        }

    protected:
        // cached data to reduce reallocation, etc.
         //convert matrix to Pardiso CSR format 
        void setMatrix(const MatrixType &matrix) {
            
            m_analysisIsOk = false;
            m_factorizationIsOk = false;

            if(!matrix.isCompressed()) {
                std::cout<<"Error in Pardiso Compute: Matrix must be compressed \n";
                return;
            }

            unsigned int nnz = matrix.nonZeros();
    
            unsigned int nno = matrix.outerSize();
            
            m_nrhs = matrix.cols();
            
            m_a = Map<const VectorType>(matrix.valuePtr(), nnz);

            m_inner_array = Map<const IntColVectorType>(matrix.innerIndexPtr(), nnz);
            m_inner_array.noalias() += IntColVectorType::Ones(nnz);
            
            m_outer_array.resize(nno+1);
            m_outer_array.head(nno) = Map<const IntColVectorType>(matrix.outerIndexPtr(),nno);
            m_outer_array(nno) = nnz;
            m_outer_array.noalias() += IntColVectorType::Ones(nno+1);

            //m_a.clear();
            //for(unsigned int jj=0; jj<nnz; ++jj) {
            //    m_innerArray.push_back(A.innerIndexPtr()[jj]+1);
            //    m_a.push_back(A.valuePtr()[jj]);
            //}
            
            
            //m_outerArray.clear();
            //need to rebuild outer array because Eigen is missing the last index
            //for(unsigned int ii=0; ii<nno; ++ii) {
                //  m_outerArray.push_back(A.outerIndexPtr()[ii] + 1);
            // }
            
            //m_outerArray.push_back(nnz+1);
            
            m_IsRowMajor = matrix.IsRowMajor;
        }

        void manageErrorCode(Index error)
        {
            switch(error)
            {
                case 0:
                    m_info = Success;
                    break;
                case -4:
                case -7:
                    m_info = NumericalIssue;
                    break;
                default:
                    m_info = InvalidInput;
            }
        }

        //Member variables
        int m_matrix_type;
    
        /* Internal solver memory pointer pt,                  */
        /* 32-bit: int pt[64]; 64-bit: long int pt[64]         */
        /* or void *pt[64] should be OK on both architectures  */
        void    *m_ptr[64];

        ComputationInfo m_info;
        bool m_initialized, m_analysisIsOk, m_factorizationIsOk;
        Index m_type, m_msglvl, m_nrhs, m_maxfct, m_num_processors, m_mnum, m_n; 
        mutable Index m_display_stats;
        mutable DoubleParameterType m_double_params;
        mutable IntParameterType m_integer_params; 
        mutable IntColVectorType m_perm;
        mutable VectorType m_a;
        mutable IntColVectorType m_outer_array;
        mutable IntColVectorType m_inner_array;
        Index m_IsRowMajor;

        //Workaround for conflicting symbols for Opensource Pardiso and MKL Pardiso
        pardiso_os::Pardiso m_pardiso;
        
    private:
        PardisoImpl(PardisoImpl &) {}
    };

    template<class Derived>
    Derived& PardisoImpl<Derived>::compute(const MatrixType& A, Index nrhs)
    {
        
        m_n = A.rows();
        eigen_assert(A.rows() == A.cols());

        pardisoRelease();
        memset(m_ptr, 0, sizeof(m_ptr));
        m_perm.setZero(m_n);
        
        setMatrix(A);
        
        //update matrix indices so that they're 1 indexed for the fortran code in pardiso
        int phase = 12;
        double   ddum = 0.;              /* Double dummy */
        int      idum = 0;              /* Integer dummy. */
        int error = 0;
        
        /*pardiso_chkmatrix(&m_matrixType, &n, m_a.data(), m_outerArray.data(), m_innerArray.data(), &error);
        if (error != 0) {
            printf("\nERROR in consistency of matrix: %d \n", error);
            exit(1);
        }*/

        m_pardiso.command(m_ptr, &m_maxfct, &m_mnum, &m_matrix_type, &phase, &m_n, m_a.data(), m_outer_array.data(),
                m_inner_array.data(), &idum, &m_nrhs, m_integer_params.data(), &m_display_stats, &ddum, &ddum, &error, m_double_params.data());
        
        if(error != 0) {
            std::cout<<"Symbolic Factorization Failed: "<<error<<"\n";
        }
        
        manageErrorCode(error);
        m_analysisIsOk = true;
        m_factorizationIsOk = true;
        m_initialized = true;
        
        return derived();
    }

    template<class Base>
    template<typename BDerived,typename XDerived>
    bool PardisoImpl<Base>::_solve(const MatrixBase<BDerived> &b, MatrixBase<XDerived>& x) const {
        
        if(m_integer_params[0] == 0) // Factorization was not computed
            return false;

        Index nrhs = Index(b.cols());
        eigen_assert(m_n==b.rows());
        eigen_assert(((MatrixBase<BDerived>::Flags & RowMajorBit) == 0 || nrhs == 1) && "Row-major right hand sides are not supported");
        eigen_assert(((MatrixBase<XDerived>::Flags & RowMajorBit) == 0 || nrhs == 1) && "Row-major matrices of unknowns are not supported");
        eigen_assert(((nrhs == 1) || b.outerStride() == b.rows()));


        //  switch (transposed) {
        //    case SvNoTrans    : m_iparm[11] = 0 ; break;
        //    case SvTranspose  : m_iparm[11] = 2 ; break;
        //    case SvAdjoint    : m_iparm[11] = 1 ; break;
        //    default:
        //      //std::cerr << "Eigen: transposition  option \"" << transposed << "\" not supported by the PARDISO backend\n";
        //      m_iparm[11] = 0;
        //  }

        Scalar* rhs_ptr = const_cast<Scalar*>(b.derived().data());
        Matrix<Scalar,Dynamic,Dynamic,ColMajor> tmp;
        
        // Pardiso cannot solve in-place
        if(rhs_ptr == x.derived().data())
        {
            tmp = b;
            rhs_ptr = tmp.data();
        }
        

        int phase = 33;
        int      idum = 0;              /* Integer dummy. */
        int error = 0;
        
        m_integer_params[7] = 1;       /* Max numbers of iterative refinement steps. */
        
        m_pardiso.command(m_ptr, &m_maxfct, &m_mnum, &m_matrix_type, &phase, &m_n, m_a.data(), m_outer_array.data(),
                m_inner_array.data(), &idum, &nrhs, m_integer_params.data(), &m_display_stats, rhs_ptr, x.derived().data(), &error, m_double_params.data());
    
        return error==0;
    }

    template<class Derived>
    Derived& PardisoImpl<Derived>::analyzePattern(const MatrixType& matrix) {
        
        m_n = matrix.rows();
        eigen_assert(matrix.rows() == matrix.cols());

        pardisoRelease();
        memset(m_ptr, 0, sizeof(m_ptr));
        m_perm.setZero(m_n);
        
        setMatrix(matrix);
        
        //update matrix indices so that they're 1 indexed for the fortran code in pardiso
        int phase = 11;
        double   ddum = 0.;              /* Double dummy */
        int      idum = 0;              /* Integer dummy. */
        int error = 0;
        
        m_pardiso.command(m_ptr, &m_maxfct, &m_mnum, &m_matrix_type, &phase, &m_n, m_a.data(), m_outer_array.data(),
                m_inner_array.data(), &idum, &m_nrhs, m_integer_params.data(), &m_display_stats, &ddum, &ddum, &error, m_double_params.data());
        
        if(error != 0) {
            std::cout<<"Symbolic Factorization Failed: "<<error<<"\n";
        }
        
        manageErrorCode(error);
        m_analysisIsOk = true;
        m_factorizationIsOk = false;
        m_initialized = true;
        return derived();
    }
 
    template<class Derived>
    Derived& PardisoImpl<Derived>::factorize(const MatrixType& matrix) {

        eigen_assert(m_analysisIsOk && "You must first call analyzePattern()");
        eigen_assert(m_n == matrix.rows() && m_n == matrix.cols());
        
        int phase = 22;
        double   ddum = 0.;              /* Double dummy */
        int      idum = 0;              /* Integer dummy. */
        int error = 0;
        
        m_pardiso.command(m_ptr, &m_maxfct, &m_mnum, &m_matrix_type, &phase, &m_n, m_a.data(), m_outer_array.data(),
                m_inner_array.data(), &idum, &m_nrhs, m_integer_params.data(), &m_display_stats, &ddum, &ddum, &error, m_double_params.data());
        
        if (error != 0) {
            printf("\nERROR during numerical factorization: %d", error);
            return 0;
        }

        manageErrorCode(error);
        m_factorizationIsOk = true;
        return derived();

    }

    //specializations for particular solvers
    template<typename MatrixType>
    class PardisoLU : public PardisoImpl< PardisoLU<MatrixType> >
    {
    protected:
        
        typedef PardisoImpl< PardisoLU<MatrixType> > Base;
        typedef typename Base::Scalar Scalar;
        typedef typename Base::RealScalar RealScalar;
        using Base::pardisoInit;
        
        friend class PardisoImpl< PardisoLU<MatrixType> >;

    public:

        using Base::compute;
        using Base::solve;

        PardisoLU(unsigned int num_processors) : Base(num_processors)
        {
            pardisoInit(Base::ScalarIsComplex ? 13 : 11);
        }

        PardisoLU(const MatrixType& matrix, unsigned int num_processors) : Base(num_processors)
        {
            pardisoInit(Base::ScalarIsComplex ? 13 : 11);
            compute(matrix);
        }

    protected:
        
        /*void getMatrix(const MatrixType& matrix)
        {
            m_matrix = matrix;
        }*/
        
    private:
        PardisoLU(PardisoLU& ) {}
    };


    namespace internal {
  
template<typename _Derived, typename Rhs>
struct solve_retval<PardisoImpl<_Derived>, Rhs>
  : solve_retval_base<PardisoImpl<_Derived>, Rhs>
{
  typedef PardisoImpl<_Derived> Dec;
  EIGEN_MAKE_SOLVE_HELPERS(Dec,Rhs)

  template<typename Dest> void evalTo(Dest& dst) const
  {
    dec()._solve(rhs(),dst);
  }
};

template<typename Derived, typename Rhs>
struct sparse_solve_retval<PardisoImpl<Derived>, Rhs>
  : sparse_solve_retval_base<PardisoImpl<Derived>, Rhs>
{
  typedef PardisoImpl<Derived> Dec;
  EIGEN_MAKE_SPARSE_SOLVE_HELPERS(Dec,Rhs)

  template<typename Dest> void evalTo(Dest& dst) const
  {
    this->defaultEvalTo(dst);
  }
};

} // end namespace internal

}

#endif
#endif

