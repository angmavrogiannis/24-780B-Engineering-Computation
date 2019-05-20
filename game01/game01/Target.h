#pragma once
#include <iostream>
#include "Missile.h"
using namespace std;


class Target {
private:
	int x, y;			//current location of target
	int sizeX, sizeY;	//current size of target
	bool isAlive;
	int step = 5;
public:

	void draw();
	void move(int scrnSizeX);
	void init();
	bool isHit(Missile theMissile);
};