#ifdef BARTELS_USE_OPENMP
    #include <omp.h>
#endif

#include <iostream>
#include <EigenTypes.h>
#include <BlockDiagonalMatrix.h>
#include <igl/Timer.H>

int main(int argc, char **argv) {

    #ifdef BARTELS_USE_OPENMP

    unsigned int num_threads = 8;
    omp_set_num_threads(num_threads);
    unsigned int modes = 101;
    unsigned int num_elements = 7008;
    unsigned int block_size = 12;
    unsigned int num_meta_blocks = 1 ;
    unsigned int meta_block_size = block_size*num_meta_blocks;;
    unsigned int num_elements_per_thread = num_elements/num_threads;
    //test with sandwhich transform
    Eigen::Matrix<double, Eigen::Dynamic, 101, Eigen::RowMajor> U;
    Eigen::BlockDiagonal<double, 12> D(num_elements/num_meta_blocks);
    Eigen::Matrix<double, 101, 101> H, H_sp;
    igl::Timer timer;

    Eigen::MatrixXd H_or = Eigen::MatrixXd::Zero(modes,modes);

    U.resize(block_size*num_elements, modes);

    U.setRandom();

    for(unsigned int ii=0; ii<D.numBlocks(); ++ii) {
        D.diagonalBlock(ii).setRandom();
        D.diagonalBlock(ii) += D.diagonalBlock(ii).transpose();
    }

    H.resize(modes,modes);
    H_sp.resize(modes,modes);
    //H_or.resize(modes,modes);

    //non-parallel sandwhich
    Eigen::MatrixXd Utmp = U;
    timer.start();

    for(unsigned int i=0; i<20; ++i) {
       // Utmp = D*U;
        H = U.transpose()*D*U;
    }
    timer.stop();

    std::cout<<"Standard: "<<timer.getElapsedTimeInSec()<<"\n";

    

    timer.start();
    for(unsigned int i=0; i<20; ++i) {
    H_sp.setZero();
    
    #pragma omp parallel
    {

         //Htmp; 
         unsigned int start_id = omp_get_thread_num()*(D.numBlocks()/num_threads);
         unsigned int start_id_elements = omp_get_thread_num()*num_elements_per_thread;
         unsigned int start_id_blocks = start_id_elements/num_meta_blocks; 

        /*#pragma omp for
        for(unsigned int ii=0; ii<D.numBlocks(); ++ii) {

            Htmp = U.block(12*ii, 0, 12, modes).transpose()*D.diagonalBlock(ii)*(U.block(12*ii, 0, 12, modes));
            
            #pragma omp critical
            {
                H_sp += Htmp;
            }
        }*/

        
       
        //this is the fastest, need to let eigen vectorize through
       
        //Eigen::MatrixXd Htmp = U.block(12*start_id, 0, 12, modes).transpose()*D.diagonalBlock(start_id)*(U.block(12*start_id, 0, 12, modes));

        //Eigen::MatrixXd Htmp = U.block(12*start_id, 0, 12*D.numBlocks()/num_threads, modes).transpose()*D.diagonalBlock(start_id)*(U.block(12*start_id, 0, 12*D.numBlocks()/num_threads, modes));
        unsigned int actual_row_size = block_size*num_meta_blocks;

        Eigen::Matrix<double, 101,101> Htmp = (U.block(12*start_id_elements, 0, actual_row_size, modes).transpose()*D.diagonalBlock(start_id_elements/num_meta_blocks))*(U.block(12*start_id_elements, 0, actual_row_size, modes));
        Eigen::Matrix<double, 12,12,Eigen::RowMajor> Dblock;
        
        for(unsigned int ii = start_id_elements+num_meta_blocks; ii < start_id_elements+num_elements_per_thread;  ii+=num_meta_blocks) {
            Dblock= D.diagonalBlock(ii/num_meta_blocks);
            Htmp.noalias() += U.block(12*ii, 0, actual_row_size, modes).transpose()*Dblock*(U.block(12*ii, 0, actual_row_size, modes));
        }

        
        

        /*for(unsigned int ii=(start_id+1); ii<(start_id + D.numBlocks()/num_threads); ii++) {

            Htmp.noalias() += U.block(12*ii, 0, 12, modes).transpose()*D.diagonalBlock(ii)*(U.block(12*ii, 0, 12, modes));
            //Htmp.noalias() += (u_blocks[ii].transpose()*diag_blocks[ii]*u_blocks[ii]);
            
        }*/

        #pragma omp critical
        {
            H_sp.noalias() += Htmp;
        }

        

    }
    }

    timer.stop();
    
    std::cout<<"Simple Parallel: "<<timer.getElapsedTimeInSec()<<"\n";

   //#pragma omp declare reduction (+: Eigen::MatrixXd: omp_out=omp_in)\
    //initializer(omp_priv=Eigen::MatrixXd::Zero(omp_orig.rows(), omp_orig.cols()))

   /*timer.start();
   for(unsigned int i=0; i<10; ++i) {

    H_or.setZero();  

 
   #pragma omp parallel 
   {
       Eigen::MatrixXd Htmp;
   #pragma omp for reduction(+:H_or) 
   for(unsigned int ii=0; ii<D.numBlocks(); ++ii) {
       Htmp = U.block(12*ii, 0, 12, modes).transpose()*D.diagonalBlock(ii)*(U.block(12*ii, 0, 12, modes));
       H_or = H_or + Htmp;
   }
   }
   }
   timer.stop();

    std::cout<<"OpenMP Reduction: "<<timer.getElapsedTimeInSec()/10.0<<"\n";*/
    //Check answers are the same
    std::cout<<"Error standard vs. Simple Parallel "<<(H - H_sp).norm()<<"\n";
    //std::cout<<"Error standard vs. OpenMP Reduction "<<(H - H_or).norm()<<"\n";
    //std::cout<<"Error standard vs. OpenMP Reduction \n"<<H<<"\n\n";
    //std::cout<<"Error standard vs. OpenMP Reduction \n"<<H_sp<<"\n";

    #endif

    return 1;
}