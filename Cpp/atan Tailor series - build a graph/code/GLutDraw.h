#pragma once
#include <windows.h>
#include <iostream>
#include <glut.h>
#include <cstdlib>
#include <cmath>
#define PI 3.14159265 
using namespace std;

void display();//main draw func
void drawPointWithCoordinates(float x, float y);
void drawCoordinateSystem(int width, int heigh);//draw coordinate lines  X  and  Y
void drawFuncAtan(int width, int heigh);