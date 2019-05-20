#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"

int getScreenCoords(float x, float y, int &screenX, int &screenY)
{
	screenX = int(100 * (x + 1)); //transformation of a physical coordinate to a screen coordinate
	screenY = int(100 * (3 - y));
	return 0;
}


int drawWall(void)
{
	int i;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(100, 0);
	glVertex2i(100, 600);
	glEnd();
	glBegin(GL_LINES);
	for (i = 0; i < 600; i += 50) { //Illustrating the fixture by drawing multiple inclined parallel lines
		glVertex2i(100, i);
		glVertex2i(50, i + 50);
	}
	glEnd();
	glFlush();
	return 0;
}

int drawMass(float L, float h, int screenX, int screenY)
{
	glColor3ub(0, 0, 0); //This function uses the previous function, getScreenCoords
	glBegin(GL_QUADS);   //Gets screen coordinates for the vertices of the rectangle(mass)
	getScreenCoords(L, 0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L + h, 0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L + h, -0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L, -0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	glEnd();
	glFlush();
	return 0;
}

int drawSpring(float L, float h, int screenX, int screenY)
{
	glColor3f(0.0, 0.0, 1.0); //Using Line Strip, we can draw the spring, following the dimensions
	glBegin(GL_LINE_STRIP);   //given by the assignment.
	glVertex2i(100, 300);
	getScreenCoords(L / 3, 0, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L / 3 + L / 36, -0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L / 3 + L / 36 + L / 18, 0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L / 3 + L / 36 + 2 * L / 18, -0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L / 3 + L / 36 + 3 * L / 18, 0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L / 3 + L / 36 + 4 * L / 18, -0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L / 3 + L / 36 + 5 * L / 18, 0.5 * h, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(2 * L / 3, 0, screenX, screenY);
	glVertex2i(screenX, screenY);
	getScreenCoords(L, 0, screenX, screenY);
	glVertex2i(screenX, screenY);
	glEnd();
	glFlush();
	return 0;
}