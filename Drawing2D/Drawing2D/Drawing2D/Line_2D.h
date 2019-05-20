#pragma once

class Line2D {
protected:
	struct Line {
		int x1, y1, x2, y2;
		int color[3];
	};
	Line theLine;
public:
	Line2D();
	void draw() const;
	void zoom(double, double, double, double &, double);
	void move(int, int, int, int);
	void makeFromString(char *);
};