#pragma once
#include <windows.h>
#include <iostream>
#include <glut.h>
#include <cstdlib>
#include <cmath>
using namespace std;

float calkAtanValue(float x, float accuracy, bool controlPrint);//calculate Y = atan(X) using Tailor series and compare this Y value with true value from library
																//if controlPrint == 1 - write information to console, else - no







