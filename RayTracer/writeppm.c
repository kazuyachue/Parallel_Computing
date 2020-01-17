//
// Torbert, 8 February 2016
//
#include <stdio.h>
//
#define M 640
#define N 480
//
int main(void)
{
   int rgb[N][M][3] ; // red-green-blue for each pixel
   //
   int y , x ;
   //
   FILE* fout ;
   //
   for( y = 0 ; y < N ; y++ )
   {
      for( x = 0 ; x < M ; x++)
      {
         rgb[y][x][0] = 0   ; // red
         rgb[y][x][1] = 255 ; // green
         rgb[y][x][2] = 0   ; // blue
      }
   }
   //
   //
   //
   fout = fopen( "allgreen.ppm" , "w" ) ;
   //
   fprintf( fout , "P3\n" ) ;
   fprintf( fout , "%d %d\n" , M , N ) ;
   fprintf( fout , "255\n" ) ;
   //
   for( y = 0 ; y < N ; y++ )
   {
      for( x = 0 ; x < M ; x++)
      {
         fprintf( fout , "%d %d %d\n" ,
          rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
      }
   }
   fclose( fout ) ;
   //
   return 0 ;
}
//
// end of file
//
