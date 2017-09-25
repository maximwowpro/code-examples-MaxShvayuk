#include "quick_sort.h"
#include <time.h>

static void swap(int anArray[], int aLeftIndex, int aRightIndex);
static int mediana(int anArray[], int aLeftIndex, int aRightIndex);

int partitionIt(int anArray[], int aLeftIndex, int aRightIndex, int aPivot)//return element, which separate array 
{
	int theLeft = aLeftIndex - 1;
	int theRight = aRightIndex;
	
	while (1)
	{
		// search the bigest element
		while (anArray[++theLeft] < aPivot);
	
		// search the lowest element
		while (theRight > 0 && anArray[--theRight] > aPivot);
	
		if (theLeft >= theRight) // pointer are the same 
		{
			break;
		}
		else
		{
			//lets to swap elements
			int theTmp = anArray[theLeft];
			anArray[theLeft] = anArray[theRight];
			anArray[theRight] = theTmp;
		}
	}

	//lets to swap elements
	int theTmp = anArray[theLeft];
	anArray[theLeft] = anArray[aRightIndex];
	anArray[aRightIndex] = theTmp;
	
	return theLeft; // return break position
}

void quickSort(int anArray[], int aLeftIndex, int aRightIndex)//recursivno sortiruet masiv
{
	if (aRightIndex - aLeftIndex <= 0)
	{
		return; // the array size equals to 1 - the array is fully sorted
	}
	
	int thePivot = anArray[aRightIndex];
	int thePartitionIndex = partitionIt(anArray, aLeftIndex, aRightIndex, thePivot);//MEDIANA
	
	//left part sorting
	quickSort(anArray, aLeftIndex, thePartitionIndex - 1);//recursion
	
	//right part sorting
	quickSort(anArray, thePartitionIndex + 1, aRightIndex);//recursion
}

int mediana(int anArray[], int aLeftIndex, int aRightIndex)//selest middle element of array and check that left<mediana<right
{
	int theCenter = (aLeftIndex + aRightIndex) / 2;// middle value of elements
	
	if (anArray[aLeftIndex] > anArray[theCenter])
	{
		swap(anArray, aLeftIndex, theCenter);
	}

	if (anArray[aLeftIndex] > anArray[aRightIndex])
	{
		swap(anArray, aLeftIndex, aRightIndex);
	}

	if (anArray[theCenter] > anArray[aRightIndex])
	{
		swap(anArray, theCenter, aRightIndex);
	}
	
	swap(anArray, theCenter, aRightIndex - 1);
	
	return anArray[aRightIndex - 1];
}

void swap(int anArray[], int aLeftIndex, int aRightIndex)//just swap 2 elements of array
{
	int theTmp = anArray[aLeftIndex];
	anArray[aLeftIndex] = anArray[aRightIndex];
	anArray[aRightIndex] = theTmp;
}

