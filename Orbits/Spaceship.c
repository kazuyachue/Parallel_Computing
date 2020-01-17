//
//Kazuya Chue, Period 5, 11/10/17
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
//
#define G 6.674e-11 //m^3 * kg^-1
#define M 5.97219e24 //kg
#define M2 7.34767309e22 //kg
#define R 6371.00e3 //m
#define R2 1737500 //m
#define D 384399861 //m
#define pi 3.14159265359
//main method
int main(int argc, char* argv[])
{
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
	double r, a, a2, ax, ay, ax1, ay1, vmag, r2, a3, ax2, ay2, vmag2, prevr; //2 is for moon, rest is spaceship 

	for(double theta = 50.0; theta < 50.1; theta+=0.1)
	{
		double angle = theta * pi / 180;
		x[0] = D / 2 * cos(angle);
		y[0] = D / 2 * sin(angle);
		vx[0] = 1600 * cos(angle);
		vy[0] = 1600 * sin(angle);

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
		/*	if(r2 < R2)
			{
				// crash
				break;
			}
			if(r < prevr)
			{
				printf("%f\n", theta);
				break;
			}		
			prevr = r; */

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
		
		//	printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", j, j*dt, x[j], y[j], moonx[j], moony[j], vx[j], vy[j], moonvx[j], moonvy[j], vmag, r); 
			printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", j, j*dt, x[j], y[j], moonx[j], moony[j], vx[j], vy[j], vmag, r); 
		}
	}
}
//
//end of file
//
