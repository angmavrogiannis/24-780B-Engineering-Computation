/*			_ _ _
	_ _ _  |	 |				Angelos Mavrogiannis
   |	 | |     |  _ _ _		Carnegie Mellon University
   |	 | |_ _ _| |	 |
   |_ _ _|		   |	 |		Simple dodge game using openGL.
				   |_ _ _|		Use arrow keys to move and dodge the red obstacles.
			 _					Colorfull obstacles grant invulerability for a few seconds.
			|_|
*/

#pragma once

struct Player {
	int x;
	int y;
	int size;
};

struct Obstacle {
	int x[50];
	double y[50];
	int dimensionX[50];
	int dimensionY[50];
	double velocity[50];
	bool isVisible[50];
};

struct Inv {
	int x;
	int y;
	int dimensionX;
	int dimensionY;
	bool beInvulnerable;
};

void invulnerable(Inv &theInv, Player thePlayer, bool &createInv, time_t &t1, time_t &invStart);

void isHit(Player thePlayer, Obstacle theObstacle, Inv theInv, bool &terminate);

void drawObstacles(Obstacle &theObstacle, int level);

void drawPlayer(Player &thePlayer);
