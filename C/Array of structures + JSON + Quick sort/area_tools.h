#ifndef area_tools_h
#define area_tools_h

#include<stdio.h>
//#include "sort_tools.h"

typedef struct dot {// dot struct for something with 2 coordinates  (x ; y)
	float x;		//coordinates X  and  Y
	float y;
} point;        


typedef struct tagSquare//  Square
{
	point points[4];//type point, array points with 4 dots, every has 2 coordinates:  X  and  Y
	float area;// AREA of every Square
} Square;


typedef struct tagSquareArray// ARRAY of Squares
{
	Square *array;// array  for  squares
	int size;//max size of squares in ARRAY
	int current_size;// number of Square with which we are working  at the moment
} SquareArray;

SquareArray *create_square_array(int Asize);//create an ARRAY of Squares

void destroySquareArray(SquareArray *aList);//destroy an ARRAY of Squares

int addSquareToList(SquareArray *aList, Square *aSquare, int MaxValueOfCoordinates);// add a Square to ARRAY
// *aList - ARRAY of KWADRATS, where we add a square 
//  *aSquare - a figure type square 

void addSeveralSquaresToList(SquareArray *aList, Square *aSquare);// add several Squares into ARRAY using funk addSquareToList


float area_square(SquareArray *ANarray);//calculate an area of Square


void json_write( FILE *file, SquareArray *aList);//write an ARRAY of Squares into .json file


void writeSquareArrayInConsole(SquareArray *aList);//write an ARRAY of Squares in console


float scan();// just scanf with checking on idiot

int printTextFromFile (FILE *aFile);//print text from file into a console and return lenght of file

void kvadrat();//print an image of square

#endif /*area_tools_h*/


