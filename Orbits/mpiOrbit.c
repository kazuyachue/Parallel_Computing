#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
// 
#include "mpi.h"
//
#define G 6.674e-11 //m^3 * kg^-1
#define M 5.97219e24 //kg
#define M2 7.34767309e22 //kg
#define R 6371.00e3 //m
#define R2 1737500 //m
#define D 384399861 //m
#define pi 3.14159265359
//
double spaceship(double angle, double velocity, double* x, double* moonx, double* y, double* moony, double* vx, double* vy, double* moonvx, double* moonvy, int n, double dt) 
{	
   	double r, a, a2, ax, ay, ax1, ay1, vmag, r2, a3, ax2, ay2, vmag2, prevr; //2 is for moon, rest is spaceship 
	
	angle = angle * pi / 180;
	x[0] = D / 2 * cos(angle);
	y[0] = D / 2 * sin(angle);
	vx[0] = velocity * cos(angle);
	vy[0] = velocity * sin(angle);

	moonx[0] = D;
	moony[0] = 0.0;
	moonvx[0] = 0;
	moonvy[0] = 1022; //m/s

	prevr = 0.0 ;

	for(int j=1; j<n; j++)
	{
		x[j] = x[j-1] + vx[j-1] * dt;
		y[j] = y[j-1] + vy[j-1] * dt;
		moonx[j] = moonx[j-1] + moonvx[j-1] * dt;
		moony[j] = moony[j-1] + moonvy[j-1] * dt;		

		r = sqrt(pow(x[j], 2) + pow(y[j],2));
		r2 = sqrt(pow(moonx[j] - x[j], 2) + pow(moony[j] - y[j],2));

		if(r2 < R2)
		{
			// crash
			return -1;
		}
		if(r < prevr)
		{
			// printf("%f\n", theta);
			return 1;
		}		
		prevr = r; 
		
		a = -1 * G * M / pow(r, 2); 	//earth's effect
		a2 = -1 * G * M2 / pow(r2, 2); 	//moon's effect
		ax = a * x[j] / r;	//earth
		ay = a * y[j] / r;	//earth
		ax1 = a2 * (x[j] - moonx[j]) / r2;	//moon
		ay1 = a2 * (y[j] - moony[j]) / r2;	//moon
		
		r2 = sqrt(pow(moonx[j], 2) + pow(moony[j],2));
		a3 = -1 * G * M / pow(r2, 2); 
		ax2 = a3 * moonx[j] / r2;
		ay2 = a3 * moony[j] / r2;
		
		vx[j] = vx[j-1] + (ax + ax1) * dt;
		vy[j] = vy[j-1] + (ay + ay1) * dt;
		moonvx[j] = moonvx[j-1] + ax2 * dt;
		moonvy[j] = moonvy[j-1] + ay2 * dt;
		vmag = sqrt(pow(vx[j], 2) + pow(vy[j],2));
	}
	
	return vmag;
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
   int        k , j  ;
   double     angle = 0.0;
   double     velocity = 1500.0;
   double     send[2];
   double     receive[3];
   double     best[3];
   //
   //
   //
   int time = 302400;
   double dt = 1;
   int n = time/dt;

   double* x = malloc(sizeof(double)*n);
   double* moonx = malloc(sizeof(double)*n);
   double* y = malloc(sizeof(double)*n);
   double* moony = malloc(sizeof(double)*n);
   double* vx = malloc(sizeof(double)*n);
   double* moonvx = malloc(sizeof(double)*n);
   double* vy = malloc(sizeof(double)*n);
   double* moonvy = malloc(sizeof(double)*n);
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
		send[0] = angle;
		send[1] = velocity;
		MPI_Send( &send , 2 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
		velocity += 100.0;
      }
      while(angle < 180.01)
      {
		MPI_Recv( &receive , 3 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
		j = status.MPI_SOURCE ;
		if(receive[2] > best[2])
		{
			best[0] = receive[0];
			best[1] = receive[1];
			best[2] = receive[2];
		}
		printf( "%d %f %f %f\n" , j , receive[0], receive[1], receive[3] ) ;
		if(velocity > 10000.0)
		{
			angle += 1.0;
			velocity = 1500.0;
		}
		send[0] = angle;
		send[1] = velocity;
		MPI_Send( &send , 2 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
		velocity += 100.0;

      }
      for( k = 1 ; k < size ; k++ )
      {
		MPI_Recv( &receive , 3 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
		if(receive[2] > best[2])
		{
			best[0] = receive[0];
			best[1] = receive[1];
			best[2] = receive[2];
		}
		//
		j = status.MPI_SOURCE ;
		//
		printf( "%d %f %f %f\n" , j , receive[0], receive[1], receive[3] ) ;
		send[0] = -1.0;
		send[1] = -1.0;
		MPI_Send( &send , 2 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
		
      }
      //
      printf( "%d %f %f %f\n" , j , best[0], best[1], best[3] ) ;
   }
   //
   // workers have rank > 0
   //
   else
   {
	while(1)
	{
		MPI_Recv( &send , 2 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
		if (send[0] < 0) break;
		receive[0] = send[0];
		receive[1] = send[1];
		receive[3] = spaceship(send[0], send[1], x, moonx, y, moony, vx, moonvx, vy, moonvy, n, dt);
		MPI_Send( &receive , 3 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD ) ;
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
