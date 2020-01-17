#include <stdio.h>
#include <math.h>

int main()
{
	FILE*fin = fopen("encoded.txt", "r");
	char tree[1234567] = {'\0'};
	int freq[256] = {0};
	int length = 28;
	int numbytes, numchars, numbits;
	double ratio, minbits;
	char ch, letter;
	//
	//skip number
	//
	fread(&ch, sizeof(char), 1, fin);
	fread(&ch, sizeof(char), 1, fin);
	fread(&ch, sizeof(char), 1, fin);

	for(int i=0;i<13;i++)
	{
		fread(&letter, sizeof(char), 1, fin);
		int index = 1;
		while(1)
		{
			fread(&ch, sizeof(char), 1, fin);
			if(ch  == '\n') break;
			
			if(ch == '0') index = index * 2;
                	else if(ch == '1') index = index * 2 + 1;
			else printf("%s\n", "Help!");			
		}	
		tree[index] = letter;
	}
	//
	//decode message
	//
	int index = 1;	
	int count = 0;
	char message[1234];
	while(1)
	{
		numbytes = fread(&ch, sizeof(char), 1, fin);
		if(numbytes == 0) break;
		
		else if(ch == '0') index = index * 2;
                else if(ch == '1') index = index * 2 + 1;
                                
		numbits++;
		
		if(tree[index]!='\0')
		{
			message[count] = tree[index];
			freq[(int)tree[index]] += 1;		
			index = 1;
			numchars++;
			count++;
		}
	}

	printf("%s\n", message);
	ratio = (8.0*numchars - numbits)/(8.0*numchars);
	printf("%s%f\n", "\nThe compression ratio is: ", ratio);
	
	//printf("%s%d\n", "Numbits: ", numbits);
	//printf("%s%d\n","Numchars: ", numchars);
	
	minbits = 0.0;
	for(int k=0; k<256; k++)
	{
		if(freq[k]!=0)
		{
			minbits += freq[k]*-((log(freq[k]*1.0/numchars))/log(2));	
		}
	}
	
	printf("%s%f\n", "\nThe theoretical minimum number of bits is: ", minbits);
	return 0;
}
