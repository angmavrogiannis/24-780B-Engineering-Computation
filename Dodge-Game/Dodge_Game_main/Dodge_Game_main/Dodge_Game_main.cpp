//Name: Angelos Mavrogiannis

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Dodge_Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

int main()
{
	string message;
	bool terminate = false, createInv = true;
	int i, key, stepSize = 10, time1 = 0, score = 0, level = 5;
	FsOpenWindow(16, 16, 800, 600, 1);
	time_t t1 = time(NULL), startGame = time(NULL);
	time_t invStart = 0;
	Player Player1;
	Player1.x = 400;
	Player1.y = 580;
	Player1.size = 20;
	Obstacle Obstacle1;
	Inv Inv1;
	Inv1.beInvulnerable = false;
	srand(time(NULL));
	for (i = 0; i < 50; i++) { //initialize Visible table so that in the start everything is visible
		Obstacle1.isVisible[i] = false;
	}
	while (!terminate) { //terminates if player gets hit by obstacle
		FsPollDevice();
		key = FsInkey();

		switch (key) {
		case FSKEY_ESC:
			terminate = true;
			break;
		case FSKEY_LEFT:
			Player1.x -= stepSize;
			if (Player1.x < 0)
				Player1.x = 0;
			break;
		case FSKEY_RIGHT:
			Player1.x += stepSize;
			if (Player1.x > 800)
				Player1.x = 800;
			break;
		case FSKEY_UP:
			Player1.y -= stepSize;
			if (Player1.y < 100)
				Player1.y = 100;
			break;
		case FSKEY_DOWN:
			Player1.y += stepSize;
			if (Player1.y > 600)
				Player1.y = 600;
			break;
		}
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glRasterPos2i(250, 50);  // sets position
		glColor3ub(255, 0, 0);
		message = "Dodge Game    Score = " + to_string(score);
		YsGlDrawFontBitmap20x32(message.c_str());
		drawPlayer(Player1);
		drawObstacles(Obstacle1, level);
		time_t t2 = time(NULL);
		score = (t2 - startGame) % 10000;
		if (score >= 20 && score < 30)
			level = 6;
		else if (score >= 30 && score <= 50)
			level = 7;
		else
			level = 8;
		if (t2 - t1 >= 3) {
			invulnerable(Inv1, Player1, createInv, t1, invStart);
		}
		time_t invStop = time(NULL);
		if (invStop - invStart >= 4)
			Inv1.beInvulnerable = false;
		else {
			glColor3ub(0, 0, 0);
			glRasterPos2i(400, 300);  // sets position
			YsGlDrawFontBitmap20x32("Invulnerable");
		}
		isHit(Player1, Obstacle1, Inv1, terminate);
		FsSwapBuffers();
		FsSleep(25);
	}

	return 0;
}