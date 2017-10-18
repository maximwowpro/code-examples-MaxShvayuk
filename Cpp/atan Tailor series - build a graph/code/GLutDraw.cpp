#include"GLutDraw.h"
#include "Function.h"
#include <windows.h>
#include <iostream>
#include <glut.h>
#include <cstdlib>
#include <cmath>
#define PI 3.14159265 
using namespace std;

int WinWidth = 1000,
WinHeigh = 480,
WinFar = 10,//depth
koef = 100;// koeficient, on which we should  * every result of counting to draw it correctly
		  //change koef to change the size(mashtab of your fraphik)

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//clear the Window and draw background at the common colour 
	drawCoordinateSystem(WinWidth, WinHeigh);
	drawFuncAtan(WinWidth, WinHeigh);
	drawPointWithCoordinates(0.8, 0.1);
	glFlush();//display our buffer to the Window
}

void drawFuncAtan(int width, int heigh)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	float x = -20;
	for (int i = -300; i < 200; i++)
	{
		glVertex2f(x*koef, atan(x)*koef);
		//cout << "\nx = " << x << "   y = " << atan(x);
		x += 0.1;
	}
	glEnd();

}

void drawPointWithCoordinates(float x, float accyracy)
{
	float y = calkAtanValue(x, accyracy, 0) * koef;// count Y coordinate using Tailor series
		  x = x*koef;
	int sizeOfside = 4;
	x = x - sizeOfside / 2;
	y = y + sizeOfside / 2;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x, y - sizeOfside);
	glVertex2f(x + sizeOfside, y - sizeOfside);
	glVertex2f(x + sizeOfside, y);
	glEnd();
}

void drawCoordinateSystem(int width, int heigh)
{
	int lenDash = koef/4;//set 1/2 of lenght of every coordinate dast ( chertochka черточка)
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);

	glVertex2f(-width / 2, 0);// main coordinate lines
	glVertex2f(width / 2, 0);
	glVertex2f(0, heigh / 2);
	glVertex2f(0, -heigh / 2);

	for (int i = 0; i < WinWidth / 2 / koef; i++)// X - coordinates
	{
		glVertex2f(i * koef, lenDash);//after ZERO
		glVertex2f(i * koef, -lenDash);
		glVertex2f(-i * koef, lenDash);//before ZERO
		glVertex2f(-i * koef, -lenDash);
	}

	for (float i = 0; i <WinHeigh / 2 / (koef*(PI / 4)); i += (PI / 4))// Y - coordinates
	{
		glVertex2f(-lenDash, i*koef);//upper ZERO
		glVertex2f(lenDash, i*koef);
		glVertex2f(-lenDash, -i * koef);// down ZERO
		glVertex2f(lenDash, -i * koef);
	}

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-WinWidth / 2, PI / 2 * koef);// draw lines at Y = PI/2
	glVertex2f(WinWidth / 2, PI / 2 * koef);
	glVertex2f(-WinWidth / 2, -PI / 2 * koef);// draw lines at Y = (- PI/2)
	glVertex2f(WinWidth / 2, -PI / 2 * koef);

	glEnd();
}