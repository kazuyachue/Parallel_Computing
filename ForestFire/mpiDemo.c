// 
// Torbert, 14 November 2016
// 
// MPI Demo
//    mpicc mpiDemo.c
//    time mpirun -np 4                                  a.out
//    time mpirun -np 4 --mca orte_base_help_aggregate 0 a.out
//    time mpirun -np 4 -mca btl ^openib                 a.out
// 
//    time mpirun -np 6 -machinefile hosts.txt a.out
// 
// Manager-Worker model for parallel processing.
// 
// 2 4   0.6283180000000000
// 3 4   0.9424770000000000
// 1 4   0.3141590000000000
// 
// real    0m19.140s
// user    1m3.061s
// sys     0m13.251s
// 
// htop -u smtorbert
// 
#include <stdio.h>
// 
#include "mpi.h"
// 
int main( int argc , char* argv[] )
{
   //
   // MPI variables
   //
   int        rank    ;
   int        size    ;
   MPI_Status status  ;
   int        tag = 0 ;
   //
   // other variables
   //
   int        k , j  ;
   double     prob , nbt ;
   //
   // boilerplate
   //
   MPI_Init(      &argc          , &argv ) ;
   MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
   MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
   //
   // manager has rank = 0
   //
   if( rank == 0 )
   {
      printf( "\n" ) ;
      //
      prob = 0.60 ; // everyone gets the same probability
      //
      for( j = 1 ; j < size ; j++ )
      {
         MPI_Send( &prob , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
      }
      //
      for( k = 1 ; k < size ; k++ )
      {
         MPI_Recv( &nbt , 1 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
         //
         j = status.MPI_SOURCE ;
         //
         printf( "%d %d %20.16f\n" , j , size , nbt ) ;
      }
      //
      printf( "\n" );
   }
   //
   // workers have rank > 0
   //
   else
   {
      MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
      //
      for( k = 1 ; k < 100000 ; k++ )
      for( j = 1 ; j < 100000 ; j++ )
      {
         nbt = 0.314159 * rank ; // these are the worst workers ever
      }
      //
      MPI_Send( &nbt , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD ) ;
   }
   //
   // boilerplate
   //
   MPI_Finalize() ;
   //
   return 0;
}
// 
// end of file
// 
