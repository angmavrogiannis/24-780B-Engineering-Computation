#include "Missile.h"
#include "fssimplewindow.h"

void Missile::draw()
{
	if (isVisible) {
		glColor3ub(255, 0, 0);
		glLineWidth(4.);
		glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x, y + 14);
		glEnd();
	}
}

void Missile::move()
{
	if (isVisible) {
		y += step;
		if (y < 0)
			isVisible = false;
	}
}

void Missile::init(int newX, int newY)
{
	x = newX;
	y = newY;
	isVisible = true;
}
