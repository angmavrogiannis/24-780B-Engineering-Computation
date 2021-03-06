#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "Spring-Mass.h"

int main(void)
{
	bool moveLeft = true; //variable for determining if the mass is moving to the right
	float L, h, fixedL;   //or if it's moving to the left, for the attempted animation
	int screenX, screenY;
	printf("24-780 Engineering Computation Problem Set 2-2 - Mass-Spring System\nEnter L and h:");
	scanf("%f %f", &L, &h); //get L and H values by the user, expect them to type value value (two numbers
	getScreenCoords(L, h, screenX, screenY); //divided by a space key.
	FsOpenWindow(16, 16, 800, 600, 1);
	fixedL = L; //get the fixed dimension of the spring, since we are going to change L for the animation
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	while (FSKEY_ESC != FsInkey())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //attempt an animation-like outcome
		drawWall();	//by drawing the wall, mass, spring at consequent locations and each time clearing the window
		drawMass(L, h, screenX, screenY);
		drawSpring(L, h, screenX, screenY);
		if (moveLeft) {
			L -= 0.05; //move to the left 
			if (L < 1) { //the value of 1 made sense to me for being the maximum displacement of the spring
				moveLeft = false;
			}
		}
		else {
			L += 0.05; //move to the right
		}
		if (L >= fixedL) {
			moveLeft = true;
		}
		FsSwapBuffers();
		FsPollDevice();
		FsSleep(50);
	}
	return 0;
}