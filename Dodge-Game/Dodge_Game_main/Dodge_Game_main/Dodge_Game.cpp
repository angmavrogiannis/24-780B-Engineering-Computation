//Name: Angelos Mavrogiannis

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Dodge_Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

void invulnerable(Inv &theInv, Player thePlayer, bool &createInv, time_t &t1, time_t &invStart)
{
	if (createInv) {
		theInv.dimensionX = rand() % 40 + 20;
		theInv.dimensionY = rand() % 40 + 20;
		theInv.x = rand() % 800;
		theInv.y = 100;
		createInv = false;
	}
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex2i(theInv.x, theInv.y - theInv.dimensionY);

	glColor3ub(0, 255, 0);
	glVertex2i(theInv.x + theInv.dimensionX, theInv.y - theInv.dimensionY);

	glColor3ub(0, 0, 255);
	glVertex2i(theInv.x + theInv.dimensionX, theInv.y);

	glColor3ub(255, 255, 0);
	glVertex2i(theInv.x, theInv.y);
	glEnd();
	bool leftCollision = thePlayer.x + thePlayer.size * 0.5 > theInv.x;
	bool rightCollision = thePlayer.x - thePlayer.size * 0.5 < theInv.x + theInv.dimensionX;
	bool upCollision = thePlayer.y > theInv.y - theInv.dimensionY;
	bool downCollision = thePlayer.y - thePlayer.size < theInv.y;
	if (leftCollision && rightCollision && upCollision && downCollision) {
		theInv.beInvulnerable = true;
		invStart = time(NULL);
	}
	theInv.y += 3;
	if (theInv.y - theInv.dimensionY > 600) {
		t1 = time(NULL);
		createInv = true;
	}

}

void isHit(Player thePlayer, Obstacle theObstacle, Inv theInv, bool &terminate)
{
	for (int i = 0; i < 50; i++) {
		bool leftCollision = thePlayer.x + thePlayer.size * 0.5 >= theObstacle.x[i];
		bool rightCollision = thePlayer.x - thePlayer.size * 0.5 <= theObstacle.x[i] + theObstacle.dimensionX[i];
		bool upCollision = thePlayer.y >= theObstacle.y[i] - theObstacle.dimensionY[i];
		bool downCollision = thePlayer.y - thePlayer.size <= theObstacle.y[i];
		if (leftCollision && rightCollision && upCollision && downCollision && !theInv.beInvulnerable)
			terminate = true;
	}
}

void drawObstacles(Obstacle &theObstacle, int level)
{
	int obstacleCount = 0;
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 50; i++) { //set random screen coords and dimensions for 5 different obstacles
		if (!theObstacle.isVisible[i]) {
			theObstacle.dimensionX[i] = rand() % 40 + 20;
			theObstacle.dimensionY[i] = rand() % 40 + 20;
			theObstacle.x[i] = rand() % 800;
			theObstacle.y[i] = 100;
			theObstacle.velocity[i] = rand() % level + 2;
			theObstacle.isVisible[i] = true;
		}
		if (theObstacle.isVisible[i]) {
			if (i <= 40)
				glBegin(GL_QUADS);
			else
				glBegin(GL_LINE_LOOP);
			glVertex2d(theObstacle.x[i], theObstacle.y[i] - theObstacle.dimensionY[i]);
			glVertex2d(theObstacle.x[i] + theObstacle.dimensionX[i], theObstacle.y[i] - theObstacle.dimensionY[i]);
			glVertex2d(theObstacle.x[i] + theObstacle.dimensionX[i], theObstacle.y[i]);
			glVertex2d(theObstacle.x[i], theObstacle.y[i]);
			glEnd();
			theObstacle.y[i] += theObstacle.velocity[i] / 2;
			if (theObstacle.y[i] - theObstacle.dimensionY[i] > 600)
				theObstacle.isVisible[i] = false;
		}
	}
}

void drawPlayer(Player &thePlayer)
{
	glColor3ub(0, 255, 0);
	glBegin(GL_QUADS);

	// base rectangle
	glVertex2i(thePlayer.x - thePlayer.size * 0.5, thePlayer.y - thePlayer.size);
	glVertex2i(thePlayer.x + thePlayer.size * 0.5, thePlayer.y - thePlayer.size);
	glVertex2i(thePlayer.x + thePlayer.size * 0.5, thePlayer.y);
	glVertex2i(thePlayer.x - thePlayer.size * 0.5, thePlayer.y);
	glEnd();
}