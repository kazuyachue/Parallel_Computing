//
// Kazuya Chue, 13 September 2017, Period 5
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
typedef struct Node
{
	char symbol;
	//
	int frequency;
	//
	struct Node* left;
	struct Node* right;
	//
} TreeNode;
//
//walk method
//
char codewords[256][1000];
void walk(TreeNode* t, char* route, int depth)
{
	if(t -> left == NULL && t -> right == NULL)
	{
		//strcpy(codewords[t->symbol], route);
		sprintf(codewords[t->symbol], "%s" , route);
		//printf("%c %s %s\n", t->symbol , route , "strcpy'ed");
		//codewords[t->symbol] = route;
	}
	else
	{
		// left
		route[depth] = '0';
		route[depth+1] = '\0';
		walk(t -> left, route, depth+1); 
		// right
		route[depth] = '1';
		route[depth+1] = '\0';
		walk(t -> right, route, depth+1); 
	}

}
//
//printTree method
//
void printTree(TreeNode* t)
{
	if(t->left == NULL && t-> right == NULL)
	{
		printf("%c%s\n", t->symbol, codewords[t->symbol]);
	}
	else
	{
		if(t->left != NULL) printTree(t -> left);
		if(t->right != NULL) printTree(t -> right);
	}

}
//
//
//
int main( int argc , char* argv[] )
{
	int freq[256] = {0};
	int numchars = 0;
	TreeNode* trees[256] = {NULL};
	
	char message[1234567];	

	int numbytes;
	char ch;
	FILE* fin = fopen("message.txt", "r");
	int counter = 0;
	while(1)
	{
		numbytes = fread( &ch , sizeof(char) , 1 , fin ) ;
		//
		if( numbytes == 0 ) break ;
		//
		if( ch!='\n')
		{
			message[counter] = ch;
			message[counter+1] = '\0'; 
			freq[ch]++;
			counter++;
		}
	}	


	/*frequency count from console input message
	for(int i=0; i<strlen(message); i++)
	{
		freq[(int)message[i]]++;
	}*/
	
	//creating trees
	int count = 0;	
	for(int j=0;j<256;j++)
	{
		if(freq[j]!=0) 
		{
			//printf("%c %d\n", j, freq[j]);
			//
			TreeNode* t = NULL;
			t = (TreeNode*)malloc( sizeof(TreeNode) );
			t -> symbol = j ;//+ '0'; //converting int to char
			t -> frequency = freq[j];
			t -> left = NULL ;
			t -> right = NULL ;
			trees[count] = t;
			count++;
			numchars++;
			//printf("%d\n",count); 
		}
	}
	
	//combining trees
	while(count>1)
	{
		for(int i = 0; i<count-1; i++)
		{
			if(trees[i] -> frequency < trees[i+1] -> frequency)
			{
				TreeNode* temp = trees[i];
				trees[i] = trees[i+1];
				trees[i+1] = temp;
			}
		}
		for(int i = 0; i<count-2; i++)
		{
			if(trees[i] -> frequency < trees[i+1] -> frequency)
			{
				TreeNode* temp = trees[i];
				trees[i] = trees[i+1];
				trees[i+1] = temp;
			}
		}
		//printf("%s\n", "Trees combined1");
		TreeNode* t = NULL;
		t = (TreeNode*)malloc( sizeof(TreeNode ) );
		t -> symbol = '\0'; 
		t -> frequency = trees[count-1]-> frequency + trees[count-2] -> frequency;
		t -> left = trees[count-1];
		t -> right = trees[count-2];
		trees[count-2] = t;
		count--;
		//printf("%d\n",count); 
	}
	TreeNode* root = trees[0];
	//printf("%s\n", "does it reach this?");
	
	//walking the tree
	char a[1000];
	walk(root, a, 0);
	
	/*printf("%s\n", "does it reach this?2");
	for(int i=0; i<256; i++)
	{
		if(freq[i]>0) printf("%c %s\n", i, codewords[i]);
	}*/

	//print stuff
	printf("%d\n", numchars);

	printTree(root);

	for(int i=0; i<strlen(message); i++)
	{
		printf("%s", codewords[message[i]]);
	}
	printf("\n");

	return 0;
}
//
//end of file
//
/*
15
K0000
H0001
e0010
d0011
a010
o011
l100
 101
z11000
y11001
r1101
m11100
f11101
w11110
u11111
000100101001000111011111001111011000011101111011101011111001010000010110001111111001010
*/
