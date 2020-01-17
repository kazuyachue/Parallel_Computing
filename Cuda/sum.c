#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//
int main(int argc, char* argv[])
{
	int numbers[8] = {3, 1, 4, 1, 5, 9, 2, 6};
	int n = 8;
	int store[n/2][n];
	for(int j=0; j < n; j++)
	{
		store[3][j] = numbers[j]; 
	} 
	
	for(int k = 1; k < n/2; k++)
	{
		int max = 8 / pow(2,k);
		int i;
		#pragma omp parallel for private(i)
		for(i=0; i<max; i=i+2) 
		{
			store[k][i] = store[k-1][i] + store[k-1][i+1];		
		}
	}
	printf("%d\n", store[3][0]);
}
