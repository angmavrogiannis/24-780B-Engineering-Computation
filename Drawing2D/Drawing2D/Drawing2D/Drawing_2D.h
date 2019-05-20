#pragma once
#include "Line_2D.h"

using namespace std;

class Drawing2D {
protected:
	Line2D *theLines;
	int numberOfLines;
public:
	Drawing2D();
	~Drawing2D();
	void readFile(const string);
	void draw() const;
	void zoom(double, double, double, double &) const;
	void move(int, int, int, int) const;
	void cleanUp();
};
