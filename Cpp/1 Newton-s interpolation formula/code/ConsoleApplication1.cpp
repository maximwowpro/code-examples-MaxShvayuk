#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "math.h"
#include "laba3_tools.h"
using namespace std;


int main()
{

	int size = 12;
	cout << "Hello! Give me the size of your array pls\nsize = "; 
	//cin >> size;
	float *X_val = new float[size];//array with X - values
	float *Y_val = new float[size];//array with Y - values
	float *difference = new float[size - 1];//array with values of difference between  X(i+1) and  X(i) 
	float step = 0.1234;//difference between X_val[i] and X_val[i+1]
	float xZero = 0.5846;// X  value for which we will search  Y using Newton formula

	for (int i = 0; i < size; i++)
	{
		X_val[i] = 0.2718 + step*i;
		Y_val[i] = atan(X_val[i]);
	}

	printTable(X_val, Y_val, size);//print image of our table vith  X  and  Y

	//fill_table(X_val, Y_val, size);//fill a table with  X  and  Y  values

	float countedResult = NewtonFormulaFirst(X_val, Y_val, difference, size, xZero, step);// count Y value using 1 Newton's formula
	comparisonWithLibraryAtan(xZero, countedResult);// count absolute & relative errors

	system("pause");
    return 0;
}

