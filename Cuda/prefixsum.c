#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//
int main(int argc, char* argv[])
{
	int n = 8;
	int A[8] = {3, 1, 4, 1, 5, 9, 2, 6};
	int B[4][8] = {};
	int C[4][8] = {};
	int i, h;
	for(i=0; i<n; i++)
	{
		B[0][i] = A[i];
	}
	for(h=1; h<4; h++)
	{
		for(i = 0; i < pow(2,3-h); i++)
		{
			B[h][i] = B[h-1][2*i] + B[h-1][2*i+1];
		}
	}
	for(h = 3; h>=0; h--)
	{
		for(i = 0; i < pow(2, 3-h); i++)
		{
			if(i==0)
			{
				C[h][i] = B[h][i];
			}
			else if(i%2==1)
			{
				C[h][i] = C[h+1][i/2];
			}
			else
			{
				C[h][i] = C[h+1][(i-1)/2] + B[h][i];
			}
		}
	}
	for(h = 3; h>=0; h--)
	{
		for(i = 0; i<n; i++)
		{
			printf("%d\t", C[h][i]);
		}
		printf("\n");
	}
}
