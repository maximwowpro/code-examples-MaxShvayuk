#include <windows.h>
#include <iostream>
#include <glut.h>
#include <cstdlib>
#include <cmath>
#include "GLutDraw.h"
#include "Function.h"
#define PI 3.14159265 
using namespace std;

int main(int argc, char**argv)
{
	calkAtanValue(0.8, 0.001, 1);

	int WinWidthM = 1000, WinHeighM = 480, WinFarM = 10;//depth
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WinWidthM, WinHeighM);//set size of window

	glutInitWindowPosition(220, 120);//set coordinates of create the window (how much pixels are betwen left hight corner of winprogram and monitor)
	glutCreateWindow("laba2");//create a title of window
	glClearColor(0, 0, 0, 1.0);//set common colour
	glOrtho(-WinWidthM / 2, WinWidthM / 2, -WinHeighM / 2, WinHeighM / 2, -WinFarM / 2, WinFarM / 2);//set dekart system of coordinates with 0-point in centre of window

	glutDisplayFunc(display);//draw function
	glutMainLoop();//in this loop glut is drawing the image
	return 0;
	
}