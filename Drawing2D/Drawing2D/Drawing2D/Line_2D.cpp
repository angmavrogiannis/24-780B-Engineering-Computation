#include <iostream>
#include <fstream>
#include <stdlib.h> //included due to using atoi (freefood was causing an error without it)
#include "fssimplewindow.h"
#include "Line_2D.h"
#include "Drawing_2D.h"

using namespace std;

Line2D::Line2D() //constructor makes all member variables zero
{
	theLine.x1 = theLine.y1 = 0;
	theLine.x2 = theLine.y2 = 0;
	for (int i = 0; i < 3; i++) {
		theLine.color[i] = 0;
	}
}

void Line2D::makeFromString(char *lineValues) //parses .txt file's content to extract
{											  //coordinates and colors
	char *token = strtok(lineValues, " ");
	int actualValue;
	int i = 0; //used to determine which value of the C-string to store to the coordinates or colors
	while (token)
	{
		actualValue = atoi(token); //converts C-string to integer
		switch (i) {
		case 0:
			theLine.x1 = actualValue;
			break;
		case 1:
			theLine.y1 = 600 - actualValue; //flipping Y coordinate to adjust to the openGL window
			break;
		case 2:
			theLine.x2 = actualValue;
			break;
		case 3:
			theLine.y2 = 600 - actualValue;
			break;
		case 4:
			theLine.color[0] = actualValue;
			break;
		case 5:
			theLine.color[1] = actualValue;
			break;
		case 6:
			theLine.color[2] = actualValue;
			break;
		}
		token = strtok(NULL, " ");
		i++;
	}
}

void Line2D::draw() const //draws every line
{
	glColor3ub(theLine.color[0], theLine.color[1], theLine.color[2]);
	glBegin(GL_LINES);
	glVertex2i(theLine.x1, theLine.y1);
	glVertex2i(theLine.x2, theLine.y2);
	glEnd();
}

void Line2D::zoom(double locX, double locY, double newScaleFactor, double &scale, double newScale)
{
	theLine.x1 = (int)round((locX * (scale - newScale) //using Nestor's code for zooming
		+ theLine.x1 * newScale) / scale);
	theLine.y1 = (int)round((locY * (scale - newScale)
		+ theLine.y1 * newScale) / scale);
	theLine.x2 = (int)round((locX * (scale - newScale)
		+ theLine.x2 * newScale) / scale);
	theLine.y2 = (int)round((locY * (scale - newScale)
		+ theLine.y2 * newScale) / scale);
}

void Line2D::move(int locX, int locY, int prevLocX, int prevLocY)
{
	theLine.x1 += (locX - prevLocX); //using Nestor's code for paning
	theLine.y1 += (locY - prevLocY);
	theLine.x2 += (locX - prevLocX);
	theLine.y2 += (locY - prevLocY);
}




