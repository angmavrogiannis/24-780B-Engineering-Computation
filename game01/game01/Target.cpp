#include "Target.h"
#include "fssimplewindow.h"

void Target::draw()
{
	if (isAlive) {
		glColor3ub(0, 255, 255);
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x + sizeX, y);
		glVertex2i(x + sizeX, y + sizeY);
		glVertex2i(x, y + sizeY);
		glEnd();
	}
}

void Target::init()
{
	x = rand() % 800;
	y = rand() % 500;
	sizeX = rand() % (200 - 20) + 20;
	sizeY = rand() % (30 - 5) + 5;
	step = rand() % (10 - 2) + 2;
	isAlive = true;
}

bool Target::isHit(Missile theMissile)
{
	int relativeX = theMissile.getX() - x;
	int relativeY = theMissile.getY() - y;

	isAlive = (0 <= relativeX && relativeX <= sizeX
		&& 0 <= relativeY && relativeY <= sizeY);

	return isAlive;
}

void Target::move(scrnSizeX)
{
	if (isAlive) {
		x += step;
		if (x > scrnSizeX)
			x = 0;
	}
}
