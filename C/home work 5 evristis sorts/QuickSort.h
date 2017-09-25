#ifndef QuickSort_h
#define QuickSort_h

#include<stdio.h>
#include "area_tools.h"

int partitionIt(SquareArray *anArray, int aLeftIndex, int aRightIndex, float aPivot);//choose an main element
void quickSort(SquareArray *anArray, int aLeftIndex, int aRightIndex);//recurcy sort an array 

#endif /*QuickSort_h*/


