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
#define R 6371.00e3 //m
//main method
int main(int argc, char* argv[])
{
	int time = 5*60*60/2;
	double dt = 0.25;
	int n = time/dt;
	
	double x[n];
	double y[n];
	double vx[n];
	double vy[n];
	double r, a, ax, ay, vmag; 

	x[0] = 0.0;
	y[0] = R + 400000;
	vx[0] = 28000 * 1000 / 3600 *2; //28,000 km/h to m/s
	vy[0] = 0;

	for(int j=1; j<n; j++)
	{
		x[j] = x[j-1] + vx[j-1] * dt;
		y[j] = y[j-1] + vy[j-1] * dt;

		r = sqrt(pow(x[j], 2) + pow(y[j],2));
		a = -1 * G * M / pow(r, 2); 
		ax = a * x[j] / r;
		ay = a * y[j] / r;

		vx[j] = vx[j-1] + ax * dt;
		vy[j] = vy[j-1] + ay * dt;
		vmag = sqrt(pow(vx[j], 2) + pow(vy[j],2));
	
		printf("%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n", j, j*dt, x[j], y[j], vx[j], vy[j], vmag, r);		
	}
}
//
//end of file
//
