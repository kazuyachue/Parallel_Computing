// 
// to compile type... make 
// uses file named... Makefile
// 
// a.out: fireGL.c
// 	gcc fireGL.c -lGL -lGLU -lglut
// 
// tab character '\t' before gcc
// 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// 
#include <GL/glut.h>
// 
#define N     600
// 
double   t[N][N]     ; 
int    pause = 0   ; 
int    step        ; 
double xmin = -2.5;
double xmax = 2.5;
double ymin = -2.5;
double ymax = 2.5;
int maxsteps = 200;
// 
void init()
{
   int x , y ;
   //
   for( x = 0 ; x < N ; x++ )
   {
      for( y = 0 ; y < N ; y++ )
      {
	double x0 = -0.7;
	double y0 = 0.27;
	double zR = xmin + x * (xmax - xmin) / N;
	double zI = ymin + y * (ymax - ymin) / N; 
	step = 0;
	while(zR * zR + zI * zI < 4.0 && step < maxsteps)
	{
		double tempR = zR * zR - zI * zI + x0;
		zI = 2 * zR * zI + y0;
		zR = tempR;
		step += 1;
	}
	if (step == maxsteps) t[x][y] = -1.0;
	else t[x][y] = 1 - pow ( 1.0 - (1.0 * step)/(1.0 * maxsteps), 3); 
      }
   }
}
// 
void idlefunc()
{
}
void drawString( char* s )
{
   int k = 0 ;
   //
   while( s[k] != '\0' )
   {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[k]);
      //
      ++k ;
   }
}
/*
   GLUT_BITMAP_8_BY_13
   GLUT_BITMAP_9_BY_15
   GLUT_BITMAP_TIMES_ROMAN_10
   GLUT_BITMAP_TIMES_ROMAN_24
   GLUT_BITMAP_HELVETICA_10
   GLUT_BITMAP_HELVETICA_12
   GLUT_BITMAP_HELVETICA_18
*/
void conv( int n , char* str )
{
}
void resetScreen()
{
   int    x  , y  ;
   //
   double x1 , y1 ;
   double x2 , y2 ;
   double x3 , y3 ;
   //
   char stepstr[20]; // overkill... 20 digits
   //
   glClear(GL_COLOR_BUFFER_BIT); // white
   //
   for( x = 0 ; x < N ; x++ )
   {
      for( y = 0 ; y < N ; y++ )
      { 
         if( t[x][y] < 0.0 ) 
         {
	      glColor3f( 1.0, 1.0, 1.0) ; 
    	 }
         else
         {
            glColor3f( 0.5 * t[x][y] , 0.5 * t[x][y], 0.5 * t[x][y]) ; // purple
         }
         //
         glBegin(GL_POINTS);
         glVertex2f(x,y);
         glEnd();
      }
   }
}
void displayfunc()
{
   int    x  , y  ;
   //
   double x1 , y1 ;
   double x2 , y2 ;
   double x3 , y3 ;
   //
   char stepstr[20]; // overkill... 20 digits
   //
   glClear(GL_COLOR_BUFFER_BIT); // white
   //
   for( x = 0 ; x < N ; x++ )
   {
      for( y = 0 ; y < N ; y++ )
      { 
         if( t[x][y] < 0.0 ) 
         {
	      glColor3f( 1.0, 1.0, 1.0) ; 
    	 }
         else
         {
            glColor3f( 0.5 * t[x][y] , 0.5 * t[x][y], 0.5 * t[x][y]) ; // purple
         }
         //
         glBegin(GL_POINTS);
         glVertex2f(x,y);
         glEnd();
      }
   }
   //
   glutSwapBuffers(); // single buffering... call glFlush();
}
void reshapefunc(int wscr,int hscr)
{
   glViewport(0,0,(GLsizei)N,(GLsizei)N);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0,1.0*N,0.0,1.0*N); // always a square
   glMatrixMode(GL_MODELVIEW);
}
void mousefunc(int button,int state,int xscr,int yscr)
{
   if(button==GLUT_LEFT_BUTTON)
   {
      if(state==GLUT_DOWN)
      {
	//zoom in
	double xpos = (xscr * 1.0) / N;
	double ypos = 1.0 - ((yscr * 1.0) / N);
	double width = xmax - xmin;
	double length = ymax - ymin;
	xmax = xmin + (xpos + 0.25) * width;
	xmin = xmin + (xpos - 0.25) * width;
	ymax = ymin + (ypos + 0.25) * length;
	ymin = ymin + (ypos - 0.25) * length;

	init();
	displayfunc();
      }
   }
   else if(button==GLUT_RIGHT_BUTTON)
   {
      if(state==GLUT_DOWN)
      {
	//zoom out
	double xpos = (xscr * 1.0) / N;
	double ypos = 1.0 - ((yscr * 1.0) / N);
	double width = xmax - xmin;
	double length = ymax - ymin;
	xmax = xmin + (xpos + 1.00) * width;
	xmin = xmin + (xpos - 1.00) * width;
	ymax = ymin + (ypos + 1.00) * length;
	ymin = ymin + (ypos - 1.00) * length;

	init();
	displayfunc();
      }
   }
}
void keyfunc(unsigned char key,int xscr,int yscr)
{
	if( key == 'r' )
	{
		//reset

		xmin = -2.5;
		xmax = 2.5;
		ymin = -2.5;
		ymax = 2.5;

		init();
		displayfunc();
	}
	else if( key == 'q' )
	{
		exit( 0 ) ;
	}
}
void redline(int xscr, int yscr)
{
	resetScreen();
	double x0 = xmin + xscr* (xmax - xmin) / N;
	double y0 = ymin + yscr * (ymax - ymin) / N; 
	double zR = 0.0;
	double zI = 0.0;	
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d((int)((0.0 - xmin)/(xmax - xmin) * N), (int) ((0.0 - ymin)/(ymax - ymin) * N));

	step = 0;
	while(zR * zR + zI * zI < 4.0 && step < maxsteps)
	{
		double tempR = zR * zR - zI * zI + x0;
		zI = 2 * zR * zI + y0;
		zR = tempR;
		glVertex2d((int)((zR - xmin)/(xmax - xmin) * N), N - (int) ((zI - ymin)/(ymax - ymin) * N));
		glVertex2d((int)((zR - xmin)/(xmax - xmin) * N), N - (int) ((zI - ymin)/(ymax - ymin) * N));
		step += 1;
	}
	glEnd();
	glutSwapBuffers();
}
int main(int argc,char* argv[])
{  
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(N,N);
   glutInitWindowPosition(100,50);
   glutCreateWindow("");
   glClearColor(1.0,1.0,1.0,0.0);
   glShadeModel(GL_SMOOTH);
   //
   init() ;
   //
   glutIdleFunc(idlefunc);
   glutDisplayFunc(displayfunc);
   glutReshapeFunc(reshapefunc);
   glutMouseFunc(mousefunc);
   glutKeyboardFunc(keyfunc);
   //glutPassiveMotionFunc(redline);
   //
   glutMainLoop();
   //
   return 0;
}
// 
// end of file
// 
