#include"laba3_tools.h"
#include <stdio.h>
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "math.h"
using namespace std;

int factorial(int val)//count a factorial
{
	int result = 1;

	for (int i = 1; i <= val; i++)
	{
		result = result*i;
	}
	return result;
}

int fill_table(float* X_array, float* Y_array, int sizeArray)//fill arrays with  X  and  Y  values
{
	cout << "please, give me the  X  and  Y  values in sequence: \n\n";
	for (int i = 0; i < sizeArray; i++)
	{
		cout << i<<" value:\nX =  ";
		cin  >> X_array[i];
		cout << "Y = ";
		cin  >> Y_array[i];
		cout << endl;
	}
	return 0;
}

float NewtonFormulaFirst(float* X_array, float* Y_array, float* difference, int sizeArray, float Xzero_value, float step)//count an intermediate values of function, given in the table using the first Newton interpolation formula
{
	float t = (Xzero_value - X_array[0]) / step;   //count  t = ((X - X[0])/step)
	float summ = t;// t * (t-1) * (t-2) * (t-3) * ... * (t-sizeArray +2)

	for (int i = 0; i<sizeArray-1; i++)//count  delta_Y[1]  values
	{
		difference[i] = Y_array[i + 1] - Y_array[i];
	}
	cout << "\n\n\nwatch your formula:  \n\n" <<fixed<<setprecision(4)<< Y_array[0] << " + " << difference[0] * t;

	float result = Y_array[0] + t*difference[0];// count 1 and 2 members of Newton's formula

	for (int j = 0; j<sizeArray-2; j++)// count  delta_Y[2] - delta_Y[sizeArray-1]  values
	{
		for (int i = 0; i< (sizeArray -2 - j); i++)
		{
			difference[i] = (difference[i + 1]) - (difference[i]);//count every delta value
		}
		summ = summ * (t - j-1);// t * (t-1) * (t-2) * (t-3) * ... * (t-sizeArray +2)
		result = result + ((summ * difference[0]) / factorial(j + 2));
		cout << fixed<<setprecision(4)<<"  +  "<<((summ * difference[0]) / factorial(j + 2)) ;
	}
	cout << "\n\nresult :\n\nfunc(X) = func("<<Xzero_value<<") = " << result<<endl;

	return result;
}

int comparisonWithLibraryAtan(float Xzero_value, float countedValue)//comparison value, which we counted using 1 Newton's formula  with  true library ATAN value
{
	float trueVal = atan(Xzero_value);//take library value
	float absoluteError = fabs(trueVal - countedValue);
	float relativeError = (absoluteError / trueVal) * 100;
	cout << "\ntrue value = " << trueVal << "\nabsolute error = " << absoluteError << "\nrelative error = " << relativeError<<" % \n";
	return 0;
}

int printTable(float* X_array, float* Y_array, int sizeArray)//printf a table with X and Y values
{
	int currentSize = 0;
	sizeArray > 7 ? currentSize = sizeArray = 7 : currentSize = sizeArray;
	
	cout << "\n\n# | ";//print a line with numbers:  # | 1 | 2 | 3 | 4 | 5 ...
	for (int i = 0; i < sizeArray; i++)
	{
		cout << setw(6) << i<< " | ";
	}

	cout << "\nX | ";//print a line with X values:  X | X1 | X2 | X3 | X4 | X5 ...
	for (int i = 0; i < sizeArray; i++)
	{
		cout <<fixed<<setprecision(4)<< X_array[i] << " | ";
	}

	cout << "\nY | ";//print a line with Y values:  Y | Y1 | Y2 | Y3 | Y4 | Y5 ...
	for (int i = 0; i < sizeArray; i++)
	{
		cout << fixed << setprecision(4) << Y_array[i] << " | ";
	}
	return 0;
}