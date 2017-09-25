#ifndef area_tools_h
#define area_tools_h

#include<stdio.h>

void kvadrat();//print an image of square

typedef struct dot {// DOT   struct for something with 2 coordinates  (x ; y)
	float x;		//coordinates X  and  Y
	float y;
} point;         

typedef struct tagSquare//  Square
{
	point points[4];//type point, array of points with 4 dots, every has 2 coordinates:  X  and  Y
	float area;// AREA of every Square
} Square;

typedef struct tagSquareArray// ARRAY of Squares
{
	Square *array;// array  for  squares
	int size;//max size of squares in ARRAY
	int current_size;// number of Square with which we are working  at the moment
} SquareArray;

SquareArray *create_square_array(int Asize);//create an ARRAY of Squares

int addSquareToList(SquareArray *aList, Square *aSquare);// add a Square to ARRAY
// *aList - ARRAY of Squares, where we add a square 
//  *aSquare - a figure type square
  
float area_square(SquareArray *ANarray);//calculate an area of Square

float scan();// just scanf with checking on idiot

#endif /*area_tools_h*/


