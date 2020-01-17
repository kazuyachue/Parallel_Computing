//Kazuya Chue, Period 5, 10/2/2017
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//
#define W 30
#define H 40
//#define P 0.6

//Queue Array Implementation

//random method
double myrand()
{
	return (rand() % 100) / 100.0;
}

//print method
void print(char ch[H][W])
{
	for(int i=0; i<W; i++) printf("%c", '-');
	printf("\n");
	for(int i=0; i<H; i++)
	{
		for(int j=0; j<W; j++)
		{
			printf("%c", ch[i][j]);
		}
		printf("\n");
	}
	for(int i=0; i<W; i++) printf("%c", '-');
	printf("\n");
	printf("\n");
}

//making the grid
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

//setting fire on trees
int simulation(char ch[H][W])
{
	bool firesLeft = true;
	int count = 0;
	
	/*node_t *fires = NULL;
	for(int i=0; i<H; i++)
	{
		if([i][0] == '*')
		{
			int array[] = {i, 0}; 
			enqueue(&fires, *array); 
		}
	}	
	while(fires != NULL)
	{
		int array[] = &dequeue(&fires);
		int i = array[0];
		int j = array[1];
		
		if(i>0 && ch[i-1][j]=='*')  ch[i-1][j]='*';
		if(j>0 && ch[i][j-1]=='*') ch[i][j-1]='*';
		if(i<H-1 && ch[i+1][j]=='*') ch[i+1][j]='*';
		if(j<W-1 && ch[i][j+1]=='') ch[i][j+1]='*';
		ch[i][j] = ' ';
	}*/
	
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
		//if(firesLeft) print(ch);
	}
	
	return count;
}

//main method
int main(int argc, char* argv[])
{
	int rseed;
	rseed = time(NULL);
	srand(rseed);
	printf("%s%d\n", "Random number seed: ", rseed);	

	int numTrials;

	char grid[H][W];
	double numsteps;
	double probability;

	double x_peak = 0.0;
	double y_peak = 0.0;
	
	//running many times
	for(double k=0; k<1.000000001; k=k+0.005)
	{
		probability = k;
		//if(probability < 0.45) numTrials = 100;
		numTrials = 1000;
		numsteps = 0.0;
		//100 trials
		for(int j=0; j<numTrials; j++)
		{
			makeGrid(grid, probability);
			
			//set left column on fire
			for(int i=0; i<H; i++)
			{
				if(grid[i][0]=='T') grid[i][0] = '*';
			}

			numsteps += simulation(grid);
		}
		
		//printf("%s%.2f%s%d\n", "Probability | Number of Steps: ", probability, " | ", numsteps/100);
		printf("%.3f\t%.4f\n", probability, numsteps/numTrials/W);
		
		if(numsteps/numTrials/W > y_peak)
		{
			y_peak = numsteps/numTrials/W;
			x_peak = probability;
		}
	}
	
	printf("%s%.2f %.4f\n", "Peak: ", x_peak, y_peak);

	return 0;
}	
//
//end of file
//
