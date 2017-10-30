#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Function.h"
#define PI 3.14159265 
using namespace std;

float calkAtanValue(float X_argument, float accuracy, bool controlPrint)//calculate Y = atan(X) using Tailor series and compare this Y value with true value from library
{																		//if controlPrint == 1 - write information to console, else - no
	float trueValue = atan(X_argument);//take true value from library

	float valueMethodSeries = X_argument;//summ of all members of series
										 //starts from value of X_argument( X0 - first member of series)
	float k = 1, i = 3;//coefficient on which we will multiply our denominator at each iterration

	float currentIterrate = 1;//number of series member wiht which we work each iterration

	while (accuracy<fabs(currentIterrate))// fabs - absolute value of a number
	{
		if (int(k) % 2 == 0)//rotation of  +  and  -  signs
		{
			currentIterrate = 1 * ((pow(X_argument, i)) / i);//pow - degree of a number
		}
		else
		{
			currentIterrate = -1 * ((pow(X_argument, i)) / i);
		}

		valueMethodSeries = valueMethodSeries + currentIterrate;
		//	cout<<currentIterrate<<"(X^"<<i<<") / "<<i<<"  =  "<<valueMethodSeries<<endl;
		i = i + 2;
		k++;
	}
	float difference = fabs(trueValue - valueMethodSeries);// difference betwen true value and counted with our func (absolute error)
	float relativeError = (difference/trueValue)*100;

	if (controlPrint == 1)
	{
		cout << "Counted using Tailor series value:   " << valueMethodSeries << endl;
		cout << "True value:    " << trueValue << endl;
		cout << "Absolute error:    " << fixed << difference << endl;
		cout << "Relative error:    " << fixed << relativeError << " %\n\n";//fixed - print without exponent
	}
	return valueMethodSeries;
}





