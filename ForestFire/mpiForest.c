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
#include "mpi.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//
#define W 60
#define H 80
//
double myrand()
{
        return (rand() % 100) / 100.0;
}
//
void makeGrid(char grid[H][W], double prob)
{
        //making the grid       
        for(int i=0; i<H; i++)
        {
                for(int j=0; j<W; j++)
                {
                        if(myrand() < prob) grid[i][j] = 'T';
                        else grid[i][j] = ' ';
                }
        }
}
//
int simulation(char ch[H][W])
{
        bool firesLeft = true;
        int count = 0;
	while(firesLeft)
	{
		firesLeft = false;
		//find fire
		for(int i=0; i<H; i++)
		{
			for(int j=0; j<W; j++)
			{
				//spread fire
				if(ch[i][j]=='*')
				{
					if(i>0 && ch[i-1][j]=='T')  ch[i-1][j]='!';
					if(j>0 && ch[i][j-1]=='T') ch[i][j-1]='!';
					if(i<H-1 && ch[i+1][j]=='T') ch[i+1][j]='!';
					if(j<W-1 && ch[i][j+1]=='T') ch[i][j+1]='!';
					ch[i][j] = ' ';
					firesLeft = true;
				}
			}
		}
		//change temporary ! to *
		for(int i=0; i<H; i++)
		{
			for(int j=0; j<W; j++)
			{
				if(ch[i][j]=='!') ch[i][j] = '*';
			}
		}
		count++;
	}
	return count;
}
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
   int        j  ;
   double     prob = 0.0; 
   double     nbt[2] ;
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
	for( j = 1 ; j < size ; j++ )
	{
		MPI_Send( &prob , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
		prob += 0.005;
	}
	while(prob < 1.00000001)
	{
		MPI_Recv( nbt , 2 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%d %f %f\n" , j , nbt[0], nbt[1] ) ;
		j = status.MPI_SOURCE ;
		MPI_Send( &prob , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
		prob +=0.005;
	}
	for( j = 1 ; j < size ; j++ )
	{
		MPI_Recv( nbt , 2 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD , &status ) ;
		printf( "%d %f %f\n" , j , nbt[0], nbt[1] ) ;
		prob = -1.0;
		MPI_Send( &prob , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
	}
	printf( "\n" );
   }
   //
   // workers have rank > 0
   //
   else
   {
	while(1)
	{   
		MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;

		if( prob < 0.0 ) break ;
		
		char	grid[H][W];
		double	numsteps = 0.0;
		int	numTrials;

		numTrials = 1000;
		
		int rseed;
		rseed = time(NULL);
		srand(rseed);

		for(int k=0; k<numTrials; k++)
		{
			makeGrid(grid, prob);
			
			//set left column on fire
			for(int i=0; i<H; i++)
			{
				if(grid[i][0]=='T') grid[i][0] = '*';
			}

			numsteps += simulation(grid);
		}
		numsteps = numsteps/numTrials/W;
		nbt[0] = prob;
		nbt[1] = numsteps;
		//
		MPI_Send( nbt , 2 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD ) ;
   	}
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
