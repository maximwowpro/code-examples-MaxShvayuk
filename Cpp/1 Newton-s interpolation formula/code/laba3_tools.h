#pragma once

int fill_table(float* X_array, float* Y_array, int sizeArray);//fill arrays with  X  and  Y  values

float NewtonFormulaFirst(float* X_array, float* Y_array, float* difference, int sizeArray, float Xzero_value, float step);//count an intermediate values of function, given in the table using the first Newton interpolation formula

int comparisonWithLibraryAtan(float Xzero_value, float countedValue);//comparison value, which we counted using 1 Newton's formula  with  true library ATAN value

int factorial(int val);//count a factorial

int printTable(float* X_array, float* Y_array, int sizeArray);//printf a table with X and Y values