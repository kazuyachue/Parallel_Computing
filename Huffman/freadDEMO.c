//
// Torbert, 4 Sept 2015
//
#include <stdio.h>
//
int main()
{
	FILE* fin = fopen( "decodeME.txt" , "r" ) ;
	//
	char ch ;
	//
	int n = 0 ;
	//
	int numbytes ;
	//
	while( 1 )
	{
		numbytes = fread( &ch , sizeof(char) , 1 , fin ) ;
		//
		if( numbytes == 0 ) break ;
		//
		n++ ;
		//
		printf( "%c" , ch ) ;
	}
	//
	fclose( fin ) ;
	//
	printf( "\n" ) ;
	printf( "%d\n" , n ) ;
	printf( "\n" ) ;
	//
	return 0 ;
}
//
// end of file
//
