//An Eigen block diagonal matrix

#ifndef EIGEN_BLOCKDIAGONAL_MATRIX_H
#define EIGEN_BLOCKDIAGONAL_MATRIX_H

#include <EigenTypes.h>

//Forward Declare the class
//Arg Type is the input argument type (haven't decided quite what the constructor will look like yet)


//From Eigen Tutorial
 /*template <class ArgType>
    struct traits<Circulant<ArgType> >
    {
      typedef Eigen::Dense StorageKind;
      typedef Eigen::MatrixXpr XprKind;
      typedef typename ArgType::StorageIndex StorageIndex;
      typedef typename ArgType::Scalar Scalar;
      enum { 
        Flags = Eigen::ColMajor,
        RowsAtCompileTime = ArgType::RowsAtCompileTime,
        ColsAtCompileTime = ArgType::RowsAtCompileTime,
        MaxRowsAtCompileTime = ArgType::MaxRowsAtCompileTime,
        MaxColsAtCompileTime = ArgType::MaxRowsAtCompileTime
      };
    };*/

namespace Eigen {

    /*template <typename Scalar> class BlockDiagonal;

    namespace internal {
    template<typename _Scalar>
    struct traits<BlockDiagonal<_Scalar> > {
        typedef _Scalar Scalar;
        typedef int_fast32_t StorageIndex;
        typedef Sparse StorageKind;
        typedef MatrixXpr XprKind;
        enum {
            RowsAtCompileTime = Dynamic,
            ColsAtCompileTime = Dynamic,
            MaxRowsAtCompileTime = Dynamic,
            MaxColsAtCompileTime = Dynamic,
            Flags = RowMajor | NestByRefBit | LvalueBit | MatrixBase<BlockDiagonal<_Scalar>>::Flags::CompressedAccessBit,
            SupportedAccessPatterns = InnerRandomAccessPattern
        };

    };*/
    //}

    //right now row major storage
    //inner indices are cols
    //outer indices are rows
    template<typename Scalar>
    class BlockDiagonal : public Eigen::SparseMatrix<Scalar, RowMajor>
    {
        using Index = typename SparseMatrix<Scalar, RowMajor>::Index;
        using StorageIndex = typename SparseMatrix<Scalar, RowMajor>::StorageIndex;
        
        public:
        
        using SparseMatrix<Scalar, RowMajor>::nonZeros;

        BlockDiagonal() 
        { 
            m_block_rows = 0;
            m_block_cols = 0;
        }
        

        //useful methods for block diagonal matrices
        void resize(Index num_blocks, Index block_rows) {
            
            Index total_rows = num_blocks*block_rows;
            Index total_cols = num_blocks*block_rows;

            m_block_rows = block_rows;
            m_block_cols = block_rows;
            m_num_blocks = num_blocks;

            Index outerSize = total_rows;
            m_innerSize = total_cols;

            //allocate space for matrix
            const Index nnz = num_blocks*block_rows*block_rows;

            if(nnz != nonZeros()) {
                m_data.clear();
                m_data.resize(nnz); //allocates space for inner indices and non-zeros
            }

            if (m_outerSize != outerSize || m_outerSize==0)
            {
                std::free(m_outerIndex);
                m_outerIndex = static_cast<StorageIndex*>(std::malloc((outerSize + 1) * sizeof(StorageIndex)));
                if (!m_outerIndex) internal::throw_std_bad_alloc();
                    m_outerSize = outerSize;
            }

            if(m_innerNonZeros)
            {
                std::free(m_innerNonZeros);
                m_innerNonZeros = 0; //means this is compressed
            }

            //I know the sparsity pattern for block matrices so I can set it up in compressed form directly
            //fill in outer indices
            for(unsigned int ii=0;ii<=num_blocks*block_rows;++ii) {
                m_outerIndex[ii] = ii*block_rows;
            }

            //fill in inner indides
            StorageIndex* innerIndices = m_data.indexPtr();

            for(unsigned int ii=0; ii<nnz; ++ii){
                innerIndices[ii] = block_rows*std::floor(ii/(block_rows*block_rows)) + ii%(block_rows);
            }
        }

        //need dense block operation 
        Map<MatrixXx<Scalar>> diagonalBlock(Index block_index) {

            assert(block_index < m_num_blocks);

            return Map<MatrixXx<Scalar>>(m_data.valuePtr()+block_index*m_block_rows*m_block_cols, m_block_rows, m_block_cols);
        } 
    
        SparseMatrix<Scalar, RowMajor> & toSparse() {
            return dynamic_cast<SparseMatrix<Scalar, RowMajor> &>(*this);
        }

        protected:

        Index m_block_rows;
        Index m_block_cols;
        Index m_num_blocks;

        using SparseMatrix<Scalar, RowMajor>::m_data;
        using SparseMatrix<Scalar, RowMajor>::m_outerSize;
        using SparseMatrix<Scalar, RowMajor>::m_innerSize;
        using SparseMatrix<Scalar, RowMajor>::m_outerIndex;
        using SparseMatrix<Scalar, RowMajor>::m_innerNonZeros;

    };

}

#endif
