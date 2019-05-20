#pragma once
#include <iostream>
using namespace std;


class Missile {
private:
	int x, y;
	bool isVisible;
	const static int step = -9;
public:
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void draw();
	void move();
	void init(int newX, int newY);

};