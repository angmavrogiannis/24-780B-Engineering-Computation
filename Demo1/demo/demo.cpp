/*
										Angelos Mavrogiannis
										Carnegie Mellon University
Happy Halloween     ___                 Eng. Computation, 24-780-B
				 ___)__|_               Demo
			.-*'          '*-,
		   /      /|   |\     \         The pictures used are
		  ;      /_|   |_\     ;        copyright free.
		  ;   |\           /|  ;        
		  ;   | ''--...--'' |  ;		The song used is written
		   \  ''---.....--''  /         and recorded by me.
			''*-.,_______,.-*'          
										
										
*/


#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "yspng.h"
#include <stdlib.h>
#include <chrono>
#include <cmath>
#include <ctime>

#define PI 3.141592653589793

using namespace std;

class Screen {
private:
	int color, w, h;
public:
	Screen();
	void setColor();
	void gradation();
	void showText(const char *text, int posX, int posY, int r, int g, int b);
};

class Ball {
private:
	double x, y, R;
	double vx, vy;
public:
	Ball();
	void init(double cx, double cy, double radius);
	void setColor();
	double grow();
	void draw(int r, int g, int bl);
};

class Guitar {
private:
	double x, y, string;
public:
	Guitar();
	void draw();
	void play(bool &bounce);
};

class Drums {
private:
	double x, y;
public:
	Drums();
	void draw();
	void play(bool &bounce);
};

class Note {
private:
	int x, y, vx, vy, selection;
public:
	Note();
	void draw();
	void move();
};

class Snow {
private:
	int x, y, vel;
public:
	Snow();
	void draw(bool snowball);
	void fall(bool wind);
};

class Pumpkin {
private:
	int x, y;
	double vx, vy;
public:
	Pumpkin();
	Pumpkin(int xPos, int yPos);
	void draw();
	void moveNbounce();
	void shoot(bool &ghostShoot);
};

class Ghost {
private:
	int x, y;
public:
	Ghost();
	Ghost(int xPos, int yPos);
	void draw(bool angry);
	void hover(bool &goUp);
	void run(bool &left, bool & right, bool &up, bool &down, int speed);
};

class Boy {
private:
	int x, y, handHeight, legPosition;
public:
	Boy();
	Boy(int xPos, int yPos);
	void draw(bool scared);
	void moveHands(bool goUp);
	void run(bool &left, bool & right, bool &up, bool &down, int speed, bool &legDirection);
};

class Basket {
private:
	int x, y;
public:
	Basket();
	void draw();
};

class Scythe {
private:
	int x, y;
public:
	Scythe();
	void draw();
	void run(bool left, bool right, bool up, bool down, int speed);
};

int main()
{
	bool playAnimation = true, guitarBounce = true, drumBounce = true;
	bool ghostShoot = true, leftB = true, rightB = false, upB = false, downB = false;
	bool leftG = true, rightG = false, upG = false, downG = false, legDirection = true;
	bool leftS = true, rightS = false, upS = false, downS = false, up = true, scared = true;
	int i, width = 800, height = 600, numbOfPumpkins = 1, endingText = 450;
	double radius = 100, dt = 0;
	FsOpenWindow(16, 16, width, height, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	srand(time(NULL));
	Screen theScreen;
	YsRawPngDecoder png[6]; //start loading
	png[0].Decode("curtain01.png");
	png[0].Flip();
	png[1].Decode("pumpkin.png");
	png[1].Flip();
	png[2].Decode("spooky.png");
	png[2].Flip();
	png[3].Decode("graveyard.png");
	png[3].Flip();
	png[4].Decode("bam.png");
	png[4].Flip();
	png[5].Decode("bloodmoon.png");
	png[5].Flip();
	Ball bigBall;
	Guitar theGuitar;
	Drums theDrums;
	Snow theSnow[300];
	Pumpkin thePumpkins[100];
	Pumpkin pumpkinBall(230, 360);
	Pumpkin pumpkinBall2(120, 410);
	Ghost theGhost;
	Ghost playingGhost(500, 250);
	Boy theBoy;
	Boy playingBoy(120, 420);
	Ghost startingGhost(650, 300);
	Ghost endingGhost(150, 300);
	Basket theBasket;
	Scythe theScythe;
	Note theNotes[24];
	bigBall.init(width / 2, height / 2, radius);
	
	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;

	char filename[] = "metal_song.wav";
	if (YSOK != wav.LoadWav(filename)) //load file contents to wav variable
	{
		cout << "Failed to read: " << filename << endl;
		return 1;
	}

	player.Start();
	player.PlayBackground(wav, true);

	auto t1 = chrono::high_resolution_clock::now();
	while (playAnimation) {
		theScreen.gradation();
		if (dt < 9.7) { 
			if (dt < 6.5) { //intro
				theScreen.showText("This is a silly Halloween story", 100, 100, 0, 0, 0);
				theScreen.showText("about a ghost and a boy..", 100, 150, 0, 0, 0);
				bigBall.draw(0, 0, 0);
				if (dt > 2.5) {
					playingBoy.moveHands(up);
					playingBoy.draw(0);
					startingGhost.hover(up);
					startingGhost.draw(0);
				}
				if (dt > 3 && dt < 4.5)
					theScreen.showText("Happy", 250, 500, 255, 255, 255);
				else if (dt > 4.5 && dt < 6.5)
					theScreen.showText("Happy Halloween!", 250, 500, 255, 255, 255);
			}
			else if (dt < 7.7) //countdown
				theScreen.showText("3", 400, 300, 255, 255, 255);
			else if (dt < 8.7)
				theScreen.showText("2", 400, 300, 255, 255, 255);
			else
				theScreen.showText("1", 400, 300, 255, 255, 255);
			FsSleep(20);
		}
		else if(dt < 19.3) { //music
			glRasterPos2d(0.0, (double)(600 - 1));
			glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, png[0].rgba);
			if (dt < 14.4) 
				theScreen.showText("John and Casper were playing music.", 60, 570, 0, 0, 0);
			else { //generating notes
				theScreen.showText("The Ghost Inside", 220, 220, 0, 0, 0);
				theScreen.showText("even though ghosts have no hands!", 60, 570, 0, 0, 0);
				for (i = 0; i < 24; i++) {
					theNotes[i].draw();
					theNotes[i].move();
				}
			}
			playingBoy.moveHands(up);
			playingGhost.hover(up);
			playingBoy.draw(0);
			playingGhost.draw(0);
			theGuitar.play(guitarBounce);
			theDrums.play(drumBounce);
			theGuitar.draw();
			theDrums.draw();
			FsSleep(50);
		}
		else if (dt < 33.5){ //snowing
			glRasterPos2d(0.0, (double)(600 - 1));
			glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, png[1].rgba);
			if (dt < 22.7)
				theScreen.showText("It was Halloween..", 100, 100, 255, 255, 255);
			else if (dt < 26.3)
				theScreen.showText("so it started snowing.", 100, 100, 255, 255, 255);
			else if (dt < 30)
				theScreen.showText("It got really windy!", 100, 100, 255, 255, 255);
			else {
				theScreen.showText("and the snowfall got intense!", 100, 100, 255, 255, 255);
			}
			for (i = 0; i < 100; i++) {
				if (dt >= 22.7 && dt < 30) { 
					theSnow[i].draw(0); //just snow
					if (dt < 26.3)
						theSnow[i].fall(0); //no wind
					else
						theSnow[i].fall(1); //snow and wind
				}
				else if (dt >= 30){
					theSnow[i].draw(1); //heavy snow
					theSnow[i].fall(0);
				}
			}
			FsSleep(20);
		}
		else if (dt < 48){ //pumpkin generator
			glRasterPos2d(0.0, (double)(600 - 1));
			glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, png[2].rgba);
			for (int i = 0; i < numbOfPumpkins; i++) {
				thePumpkins[i].draw();
				thePumpkins[i].moveNbounce();
			}
			if (dt < 37.4) {
				numbOfPumpkins = 10; //less pumpkins
				theScreen.showText("Casper and John decided to go", 50, 100, 255, 255, 255);
				theScreen.showText("for a walk in the woods...", 50, 150, 255, 255, 255);
			}
			else if (dt < 44) {
				numbOfPumpkins = 80; //more pumpkins
				theScreen.showText("Soon they found out that", 50, 100, 255, 255, 255);
				theScreen.showText("the place was full of pumpkins!", 50, 150, 255, 255, 255);
			}
			else {
				numbOfPumpkins = 100; //more and more pumpkins
				theScreen.showText("So they had an idea...", 50, 100, 255, 255, 255);
			}
			FsSleep(20);
		}
		else if (dt < 62){ //basketball time
			glRasterPos2d(0.0, (double)(600 - 1));
			glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, png[3].rgba);
			if (dt < 56) {
				theScreen.showText("They decided to get some pumpkins", 50, 100, 255, 255, 255);
				theScreen.showText("and play some basketball!", 50, 150, 255, 255, 255);
			}
			else if (dt < 60) {
				theScreen.showText("It was obvious that John was", 50, 100, 255, 255, 255);
				theScreen.showText("much better than Casper!", 50, 150, 255, 255, 255);
			}
			else
				theScreen.showText("So Casper got angry!!!", 50, 100, 255, 255, 255);
			if (dt < 60.3) {
				theGhost.draw(0);
				theBoy.draw(0);
				if (ghostShoot) { //ghost takes a shot
					pumpkinBall.draw();
					pumpkinBall.shoot(ghostShoot);
				}
				if (!ghostShoot) { //boy takes a shot
					pumpkinBall2.draw();
					pumpkinBall2.shoot(ghostShoot);
				}
			}
			else {
				theGhost.draw(1); //draw angry ghost (red eyes)
				theBoy.draw(1);   //draw sad boy
				theScythe.draw();
			}
			theBasket.draw();
			for (i = 0; i < 100; i++) { //keep it snowing
				theSnow[i].draw(1);
				theSnow[i].fall(0);
			}
			FsSleep(20);
		}
		else if (dt < 76.8) { //the chase
			theBoy.draw(1); 
			if (scared)
				scared = false;
			else
				scared = true;
			theGhost.draw(scared); //ghost's eyes alternate from black to red while chasing
			theScythe.draw();
			if (dt < 70) {
				theScreen.showText("He started chasing John!", 50, 100, 255, 255, 255);
				theBoy.run(leftB, rightB, upB, downB, 4, legDirection); //boy is faster at the start
				theGhost.run(leftG, rightG, upG, downG, 3);
				theScythe.run(leftG, rightG, upG, downG, 3);
			}
			else if (dt < 74) {
				theScreen.showText("Casper was catching up!", 50, 100, 255, 255, 255);
				theBoy.run(leftB, rightB, upB, downB, 4, legDirection);
				theGhost.run(leftG, rightG, upG, downG, 6); //ghost speeding up
				theScythe.run(leftG, rightG, upG, downG, 6);
			}
			else if (dt < 76) { 
				theScreen.showText("And finally......", 50, 100, 255, 255, 255);
				theBoy.run(leftB, rightB, upB, downB, 4, legDirection);
				theGhost.run(leftG, rightG, upG, downG, 6);
				theScythe.run(leftG, rightG, upG, downG, 6);
			}
			else if (dt < 76.8) { //bam
				glRasterPos2d(0.0, (double)(600 - 1)); 
				glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, png[4].rgba);
			}
			FsSleep(20);
		}
		else {
			glRasterPos2d(0.0, (double)(600 - 1));
			glDrawPixels(800, 600, GL_RGBA, GL_UNSIGNED_BYTE, png[5].rgba);
			endingGhost.hover(up); //2 ghosts hovering
			endingGhost.draw(0);
			startingGhost.hover(up);
			startingGhost.draw(0);
			if (dt < 82) {
				theScreen.showText("John became a ghost..", 220, 400, 255, 255, 255);
			}
			else if (dt < 83)
				theScreen.showText("T", 300, 450, 255, 255, 255);
			else if (dt < 84)
				theScreen.showText("TH", 300, 450, 255, 255, 255);
			else if (dt < 85)
				theScreen.showText("THE", 300, 450, 255, 255, 255);
			else if (dt < 86)
				theScreen.showText("THE E", 300, 450, 255, 255, 255);
			else if (dt < 87)
				theScreen.showText("THE EN", 300, 450, 255, 255, 255);
			else if (dt < 88)
				theScreen.showText("THE END", 300, 450, 255, 255, 255);
			else {
				theScreen.showText("That's all folks!", 220, 400, 255, 255, 255);
				theScreen.showText("THE END", 300, endingText, 255, 255, 255);
				endingText += 1;
			}
			FsSleep(20);
		}
		FsSwapBuffers();
		if (dt >= 94)
			playAnimation = false;
		FsPollDevice();

		auto t2 = chrono::high_resolution_clock::now();
		chrono::duration<double>elapsed = t2 - t1; //calculate elapsed time
		dt = elapsed.count();
	}
	return 0;
}

Screen::Screen()
{
	w = 800;
	h = 600;
}

void Screen::setColor()
{
	color = rand() % 6 + 1;
	switch (color) {
	case 1: glColor3ub(0, 0, 0); //black
		break;
	case 2: glColor3ub(47, 79, 79); //darkslategrey
		break;
	case 3: glColor3ub(119, 136, 153); //lightslategrey
		break;
	case 4: glColor3ub(128, 128, 128); //gray
		break;
	case 5: glColor3ub(255, 255, 255); //white
		break;
	case 6: glColor3ub(255, 0, 0); //red
		break;
	}
}

void Screen::gradation()
{
	glShadeModel(GL_SMOOTH);

	glBegin(GL_QUADS);

	setColor();
	glVertex2i(0, 0);

	setColor();
	glVertex2i(w, 0);

	setColor();
	glVertex2i(w, h);

	setColor();
	glVertex2i(0, h);

	glEnd();
}

void Screen::showText(const char *text, int posX, int posY, int r, int g, int b)
{
	glColor3ub(r, g, b);
	glRasterPos2i(posX, posY);  // sets position
	//glColor3ub(r, g, b);
	YsGlDrawFontBitmap20x32(text);
}

Ball::Ball()
{
	vx = 0;
	vy = 0;
}

void Ball::init(double cx, double cy, double radius)
{
	x = cx;
	y = cy;
	R = radius;
}

void Ball::setColor()
{
	int color = rand() % 7 + 1;
	switch (color) {
	case 1: glColor3ub(0, 0, 0); //black
		break;
	case 2: glColor3ub(47, 255, 0); //green
		break;
	case 3: glColor3f(1.0, 0.5, 0.0); //orange
		break;
	case 4: glColor3ub(128, 128, 128); //gray
		break;
	case 5: glColor3ub(255, 255, 255); //white
		break;
	case 6: glColor3ub(255, 0, 0); //red
		break;
	}
}

double Ball::grow()
{
	R += 1;
	return R;
}

void Ball::draw(int r, int g, int bl)
{
	double xBall, yBall, angle;
	glColor3ub(r, g, bl);
	if (true)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 64; i++) {
		angle = (double)i * PI / 32.0;
		xBall = x + cos(angle)*R;
		yBall = y + sin(angle)*R;
		glVertex2d(xBall, yBall);
	}
	glEnd();
	setColor();
	glBegin(GL_POLYGON); //1st part of mouth
	glVertex2d(x - 52.5, y + 20);
	glVertex2d(x - 52.5, y + 55);
	glVertex2d(x - 37.5, y + 55);
	glVertex2d(x - 37.5, y + 20);
	glEnd();
	glBegin(GL_POLYGON); //2nd part of mouth
	glVertex2d(x - 22.5, y + 20);
	glVertex2d(x - 22.5, y + 55);
	glVertex2d(x - 7.5, y + 55);
	glVertex2d(x - 7.5, y + 20);
	glEnd();
	glBegin(GL_POLYGON); //3rd part of mouth
	glVertex2d(x + 7.5, y + 20);
	glVertex2d(x + 7.5, y + 55);
	glVertex2d(x + 22.5, y + 55);
	glVertex2d(x + 22.5, y + 20);
	glEnd();
	glBegin(GL_POLYGON); //4th part of mouth
	glVertex2d(x + 37.5, y + 20);
	glVertex2d(x + 37.5, y + 55);
	glVertex2d(x + 52.5, y + 55);
	glVertex2d(x + 52.5, y + 20);
	glEnd();
	glBegin(GL_POLYGON); //left eye
	glVertex2d(x - 52.5, y - 20);
	glVertex2d(x - 41.25, y - 60);
	glVertex2d(x - 30, y - 20);
	glEnd();
	glBegin(GL_POLYGON); //right eye
	glVertex2d(x + 30, y - 20);
	glVertex2d(x + 41.25, y - 60);
	glVertex2d(x + 52.5, y - 20);
	glEnd();
	glBegin(GL_POLYGON); //nose
	glVertex2d(x - 20, y);
	glVertex2d(x, y - 30);
	glVertex2d(x + 20, y);
	glEnd();
}

Guitar::Guitar()
{
	x = 100;
	y = string = 300;
}

void Guitar::draw()
{
	glLineWidth(1);
	glColor3ub(0, 0, 255);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x, y + 60);
	glVertex2i(x + 100, y + 30);
	glVertex2i(x, y);
	glEnd();
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glLineWidth(0.1);
	glVertex2i(x + 20, string + 25);
	glVertex2i(x + 195, string + 25);
	glVertex2i(x + 20, string + 27);
	glVertex2i(x + 198, string + 27);
	glVertex2i(x + 20, string + 29);
	glVertex2i(x + 201, string + 29);
	glVertex2i(x + 20, string + 31);
	glVertex2i(x + 203, string + 31);
	glVertex2i(x + 20, string + 33);
	glVertex2i(x + 206, string + 33);
	glVertex2i(x + 20, string + 35);
	glVertex2i(x + 209, string + 35);
	glEnd();
	glColor3ub(0, 0, 255);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x + 190, y + 20);
	glVertex2i(x + 190, y + 40);
	glVertex2i(x + 230, y + 40);
	glEnd();
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glEnd();
}

void Guitar::play(bool &bounce)
{
	if (bounce) {
		string += 3;
		bounce = false;
	}
	else {
		string -= 3;
		bounce = true;
	}
}

Drums::Drums()
{
	x = 400;
	y = 300;
}

void Drums::draw()
{
	glColor3ub(0, 255, 0);
	glBegin(GL_POLYGON); //drawing tom 1
	glVertex2i(x, y);
	glVertex2i(x + 60, y);
	glVertex2i(x + 60, y + 50);
	glVertex2i(x, y + 50);
	glEnd();
	glBegin(GL_POLYGON); //drawing tom 2
	glVertex2i(x + 50, y - 45);
	glVertex2i(x + 90, y - 45);
	glVertex2i(x + 90, y - 10);
	glVertex2i(x + 50, y - 10);
	glEnd();
	glBegin(GL_POLYGON); //drawing tom 3
	glVertex2i(x + 120, y - 45);
	glVertex2i(x + 160, y - 45);
	glVertex2i(x + 160, y - 10);
	glVertex2i(x + 120, y - 10);
	glEnd();
	glBegin(GL_POLYGON); //drawing snare
	glVertex2i(x + 170, y - 30);
	glVertex2i(x + 210, y - 30);
	glVertex2i(x + 210, y - 10);
	glVertex2i(x + 170, y - 10);
	glEnd();
	double xBass, yBass, angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 64; i++) {
		angle = (double)i * PI / 32.0;
		xBass = x + 120 + cos(angle)*55;
		yBass = y + 50 + sin(angle)*55;
		glVertex2d(xBass, yBass);
	}
	glEnd();
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(x + 30, y + 50);
	glVertex2i(x + 30, y + 100);
	glVertex2i(x + 70, y - 10);
	glVertex2i(x + 70, y + 30);
	glVertex2i(x + 140, y - 10);
	glVertex2i(x + 140, y);
	glVertex2i(x + 190, y - 10);
	glVertex2i(x + 190, y + 100);
	glEnd();
	glRasterPos2i(x + 75, y + 60);  // sets position
	glColor3ub(0, 0, 0);
	YsGlDrawFontBitmap20x32("Pearl");
}

void Drums::play(bool &bounce)
{

	int xDrumstick = x, yDrumstick = y;
	if (bounce) {
		yDrumstick += 4;
		bounce = false;
		glColor3ub(0, 255, 0);
		double xBass, yBass, angle;
		glBegin(GL_POLYGON);
		for (int i = 0; i < 64; i++) {
			angle = (double)i * PI / 32.0;
			xBass = x + 120 + cos(angle) * 70;
			yBass = y + 50 + sin(angle) * 70;
			glVertex2d(xBass, yBass);
		}
		glEnd();
	}
	else {
		yDrumstick -= 4;
		bounce = true;
	}
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(xDrumstick + 60, yDrumstick - 30);
	glVertex2i(xDrumstick + 20, yDrumstick);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(xDrumstick + 170, yDrumstick - 60);
	glVertex2i(xDrumstick + 190, yDrumstick - 30);
	glEnd();
	
}

Snow::Snow()
{
	x = rand() % 800 + 1;
	y = 0;
	vel = rand() % 20 + 8;
}

void Snow::draw(bool snowball)
{
	glColor3ub(255, 255, 255);
	if (!snowball) {
		glBegin(GL_LINES);
		glVertex2i(x, y);
		glVertex2i(x, y + 5);
		glEnd();
	}
	else {
		double xSnow, ySnow, angle;
		glBegin(GL_POLYGON);
		for (int i = 0; i < 64; i++) {
			angle = (double)i * PI / 32.0;
			xSnow = x + cos(angle) * 5;
			ySnow = y + sin(angle) * 5;
			glVertex2d(xSnow, ySnow);
		}
		glEnd();
	}
}

void Snow::fall(bool wind)
{
	y += vel;
	if (y >= 600) {
		y = 0;
		x = rand() % 800 + 1;
	}
	if (wind) {
		x += 10;
	}
}

Pumpkin::Pumpkin()
{
	x = rand() % 750 + 50;
	y = rand() % 550 + 50;
	vx = rand() % 20 + 5;
	vy = rand() % 20 + 5;
}

Pumpkin::Pumpkin(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
	vx = rand() % 15 + 40;
	vy = - (rand() % 15 + 40);
}

void Pumpkin::draw()
{
	glColor3f(0, 1, 0);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glVertex2i(x, y - 20);
	glVertex2i(x, y - 25);
	int yPump = y - 25;
	for (int i = 0; i < 5; i++)
		glVertex2i(x + i, yPump - i);
	glEnd();
	glColor3f(1.0, 0.5, 0.0);
	double xPumpkin, yPumpkin, angle;
	glBegin(GL_POLYGON); //pumpkin body (circle)
	for (int i = 0; i < 64; i++) {
		angle = (double)i * PI / 32.0;
		xPumpkin = x + cos(angle) * 20;
		yPumpkin = y + sin(angle) * 20;
		glVertex2d(xPumpkin, yPumpkin);
	}
	glEnd();
	glColor3f(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_POLYGON); //left eye
	glVertex2i(x - 15, y - 5);
	glVertex2i(x - 12, y - 15);
	glVertex2i(x - 4, y - 5);
	glEnd();
	glBegin(GL_POLYGON); //right eye
	glVertex2i(x + 4, y - 5);
	glVertex2i(x + 12, y - 15);
	glVertex2i(x + 15, y - 5);
	glEnd();
	glBegin(GL_POLYGON); //mouth
	glVertex2i(x - 5, y + 5);
	glVertex2i(x, y - 3);
	glVertex2i(x + 5, y + 5);
	glEnd();
	glBegin(GL_LINE_STRIP); //green connection to tree
	glVertex2i(x - 12, y + 6);
	glVertex2i(x - 10, y + 12);
	glVertex2i(x - 8, y + 8);
	glVertex2i(x - 6, y + 12);
	glVertex2i(x - 4, y + 8);
	glVertex2i(x - 2, y + 12);
	glVertex2i(x, y + 8);
	glVertex2i(x + 2, y + 12);
	glVertex2i(x + 4, y + 8);
	glVertex2i(x + 6, y + 12);
	glVertex2i(x + 8, y + 8);
	glVertex2i(x + 10, y + 12);
	glVertex2i(x + 12, y + 6);
	glEnd();
}

void Pumpkin::moveNbounce() //handles multiple pumpkins bouncing on the walls
{
	double dt = 0.5;
	x += vx * dt;
	y += vy * dt;
	bool limit1 = (0 >= x - 20 || x + 20 >= 800);
	bool limit2 = (0 >= y - 20 || y + 20 >= 600);//bounce
	if (y - 20 <= 0) {
		y = 21;
		vy *= -1;
	}
	if (y + 20 >= 600) {
		y = 579;
		vy *= -1;
	}
	if (x - 20 <= 0) {
		x = 21;
		vx *= -1;
	}
	if (x + 20 >= 800) {
		x = 779;
		vx *= -1;
	}
	/*if (limit1)
		vx *= -1;
	if (limit2) 
		vy *= -1;*/
	/*if (limit1 && limit2) {
		x = 400;
		y = 300;*/
}

void Pumpkin::shoot(bool &ghostShoot) //modeling the basketball shoot
{
	double ax, ay, dt = 0.2; //x and y accelerations

	ax = 0.0;
	ay = 9.81; //is a positive quantity since gravity tends to move the ball down and
			   //hence increase the ball's y

	x += vx * dt;
	y += vy * dt;

	vx += ax * dt;
	vy += ay * dt;

	if (x + 20 >= 570 && y >= 120 && y <= 250) {
		vx *= -0.7;
		vy *= -1;
	}

	if (x - 20 >= 520 && x + 20 <= 570 && y <= 185) {
		vx = 0;
	}

	if (x + 20 >= 800 || y + 20 >= 600 || y - 20 <= 0 || x - 20 <= 0) {
		if (ghostShoot) {
			x = 230;
			y = 360;
			vx = rand() % 15 + 40;
			vy = -(rand() % 15 + 40);
			ghostShoot = false;
		}
		else {
			x = 120;
			y = 410;
			vx = 40;
			vy = -71;
			ghostShoot = true;
		}
	}
}

Ghost::Ghost()
{
	x = 200;
	y = 400;
}

Ghost::Ghost(int xPos, int yPos) //overloading constructor to initialize ghost
{								//in a different position than the default one
	x = xPos;
	y = yPos;
}

void Ghost::draw(bool angry)
{
	double xGhost, yGhost, angle;
	glColor3ub(255, 255, 255);
	glBegin(GL_POLYGON); //head
	for (int i = 0; i < 64; i++) {
		angle = (double)i * PI / 32.0;
		xGhost = x + cos(angle) * 30;
		yGhost = y + sin(angle) * 30;
		glVertex2d(xGhost, yGhost);
	}
	glEnd();
	glBegin(GL_POLYGON); //body
	glVertex2i(x - 30, y);
	glVertex2i(x + 30, y);
	glVertex2i(x + 30, y + 60);
	glVertex2i(x - 30, y + 60);
	glEnd();
	glLineWidth(10);
	glBegin(GL_LINE_STRIP); //bottom of the body
	glVertex2i(x - 30, y + 60);
	glVertex2i(x - 20, y + 65);
	glVertex2i(x - 10, y + 60);
	glVertex2i(x, y + 65);
	glVertex2i(x + 10, y + 60);
	glVertex2i(x + 20, y + 65);
	glVertex2i(x + 30, y + 60);
	glEnd();
	if (angry)
		glColor3f(0.5, 0, 0);
	else
		glColor3ub(0, 0, 0);
	double xEye, yEye, eyeAngle;
	glBegin(GL_POLYGON); //left eye
	for (int i = 6; i < 38; i++) {
		eyeAngle = (double)i * PI / 32.0;
		xEye = x - 10 + cos(eyeAngle) * 12;
		yEye = y - 10 + sin(eyeAngle) * 12;
		glVertex2d(xEye, yEye);
	}
	glEnd();
	glBegin(GL_POLYGON); //right eye
	for (int i = 58; i < 90; i++) {
		eyeAngle = (double)i * PI / 32.0;
		xEye = x + 10 + cos(eyeAngle) * 12;
		yEye = y - 10 + sin(eyeAngle) * 12;
		glVertex2d(xEye, yEye);
	}
	glEnd();
	glColor3ub(0, 0, 0);
	glBegin(GL_POLYGON); //mouth
	for (int i = 0; i < 64; i++) {
		angle = (double)i * PI / 32.0;
		xGhost = x +  cos(angle) * 8;
		yGhost = y + 20 + sin(angle) * 8;
		glVertex2d(xGhost, yGhost);
	}
	glEnd();
}

void Ghost::hover(bool &goUp)
{
	if (goUp){
		y -= 1;
		if (y <= 250)
			goUp = false;
	}
	else {
		y += 1;
		if (y >= 300)
			goUp = true;
	}
}

void Ghost::run(bool &left, bool & right, bool &up, bool &down, int speed)
{
	if (x - 30 <= 0) {
		left = false;
		up = true;
	}
	if (y - 70 <= 0) {
		up = false;
		right = true;
	}
	if (x + 70 >= 800) {
		right = false;
		down = true;
	}
	if (y + 60 >= 600) {
		down = false;
		left = true;
	}
	if (left)
		x -= speed;
	if (right)
		x += speed;
	if (up)
		y -= speed;
	if (down)
		y += speed;
}

Boy::Boy()
{
	x = 70;
	y = 500;
	handHeight = 120;
	legPosition = 30;
}

Boy::Boy(int xPos, int yPos) //overloading constructor to set boy in another position
{							//than the default one
	x = xPos;
	y = yPos;
	handHeight = 120;
	legPosition = 30;
}

void Boy::draw(bool scared)
{
	glColor3ub(105, 105, 105);
	glBegin(GL_LINES); //right leg
	glVertex2i(x + legPosition, y + 50);
	glVertex2i(x, y);
	glEnd();
	glBegin(GL_LINE_STRIP); //left leg and body
	glVertex2i(x - legPosition, y + 50);
	glVertex2i(x, y);
	glVertex2i(x, y - 150);
	glEnd();
	glBegin(GL_LINE_STRIP); //hands
	glVertex2i(x - 40, y - handHeight);
	glVertex2i(x, y - 70);
	glVertex2i(x + 40, y - handHeight);
	glEnd();
	double xBoy, yBoy, eyeBoy;
	glBegin(GL_POLYGON); //head
	for (int i = 0; i < 64; i++) {
		eyeBoy = (double)i * PI / 32.0;
		xBoy = x + cos(eyeBoy) * 30;
		yBoy = y - 150 + sin(eyeBoy) * 30;
		glVertex2d(xBoy, yBoy);
	}
	glEnd();
	glColor3ub(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP); //mouth
	if (!scared) {
		glVertex2i(x - 10, y - 140);
		glVertex2i(x - 5, y - 135);
		glVertex2i(x + 5, y - 135);
		glVertex2i(x + 10, y - 140);
	}
	else {
		glVertex2i(x - 10, y - 135);
		glVertex2i(x - 5, y - 140);
		glVertex2i(x + 5, y - 140);
		glVertex2i(x + 10, y - 135);
	}
	glEnd();
	glLineWidth(5);
	glBegin(GL_LINES); //eyes
	glVertex2i(x - 15, y - 160);
	glVertex2i(x - 5, y - 160);
	glVertex2i(x + 5, y - 160);
	glVertex2i(x + 15, y - 160);
	glEnd();
}

void Boy::moveHands(bool goUp)
{
	if (goUp)
		handHeight -= 1;
	else
		handHeight += 1;
}

void Boy::run(bool &left, bool &right, bool &up, bool &down, int speed, bool &legDirection)
{
	if (legDirection) {
		legPosition -= 2;
		if (legPosition <= -30)
			legDirection = false;
	}
	else {
		legPosition += 2;
		if (legPosition >= 30)
			legDirection = true;
	}
	if (x - 40 <= 0) {
		left = false;
		up = true;
	}
	if (y - 180 <= 0) {
		up = false;
		right = true;
	}
	if (x + 30 >= 800) {
		right = false;
		down = true;
	}
	if (y + 50 >= 600) {
		down = false;
		left = true;
	}
	if (left)
		x -= speed;
	if (right)
		x += speed;
	if (up)
		y -= speed;
	if (down)
		y += speed;
}

Basket::Basket()
{
	x = 620;
	y = 570;
}

void Basket::draw()
{
	glColor3ub(0, 0, 255);
	glBegin(GL_POLYGON); //support beam
	glVertex2i(x, y);
	glVertex2i(x + 30, y);
	glVertex2i(x + 30, y - 400);
	glVertex2i(x, y - 400);
	glEnd();
	glBegin(GL_POLYGON); //beam connecting basket to support beam
	glVertex2i(x, y - 400);
	glVertex2i(x - 50, y - 400);
	glVertex2i(x - 50, y - 370);
	glVertex2i(x, y - 370);
	glEnd();
	glColor3f(0.3, 0.3, 0.3);
	glLineWidth(6);
	glBegin(GL_LINES); //basket
	glVertex2i(x - 50, y - 450);
	glVertex2i(x - 50, y - 320);
	glEnd();
	glColor3f(1.0, 0.3, 0.0);
	glBegin(GL_LINES); //hoop
	glVertex2i(x - 50, y - 385);
	glVertex2i(x - 100, y - 385);
	glEnd();
	glColor3ub(255, 255, 255);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP); //net
	glVertex2i(x - 58, y - 382);
	glVertex2i(x - 92, y - 382);
	glVertex2i(x - 92, y - 350);
	glVertex2i(x - 58, y - 350);
	glEnd();
	glBegin(GL_LINES);
	for (int i = 58; i < 93; i+= 4) {
		glVertex2i(x - i, y - 382);
		glVertex2i(x - i, y - 350);
	}
	for (int j = 350; j < 383; j += 4) {
		glVertex2i(x - 92, y - j);
		glVertex2i(x - 58, y - j);
	}
	glEnd();
}

Scythe::Scythe()
{
	x = 230;
	y = 450;
}

void Scythe::draw()
{
	glColor3ub(128, 128, 128);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + 10, y);
	glVertex2i(x + 10, y - 100);
	glVertex2i(x, y - 100);
	glEnd();
	glColor3ub(0, 0, 0);
	double xScythe, yScythe, angle;
	glBegin(GL_POLYGON); //head
	for (int i = 42; i < 64; i++) { //40, 64
		angle = (double)i * PI / 32.0;
		xScythe = x + 10 + cos(angle) * 30;
		yScythe = y - 80 + sin(angle) * 30;
		glVertex2d(xScythe, yScythe);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(x, y - 85);
	glVertex2i(x - 5, y - 105);
	glVertex2i(x + 10, y - 105);
	glVertex2i(x + 10, y - 95);
	glEnd();
}

void Scythe::run(bool left, bool right, bool up, bool down, int speed)
{
	if (left)
		x -= speed;
	if (right)
		x += speed;
	if (up)
		y -= speed;
	if (down)
		y += speed;
}

Note::Note()
{
	x = 340;
	y = 400;
	vx = rand() % 30 - 5;
	vy = rand() % 10 + 2;
	selection = rand() % 4;
}

void Note::draw()
{
	glColor3ub(0, 0, 0);
	double xNote, yNote, angle;
	glLineWidth(2);
	if (selection == 0 || selection == 2)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 64; i++) {
		angle = (double)i * PI / 32.0;
		xNote = x + cos(angle) * 10;
		yNote = y + sin(angle) * 10;
		glVertex2d(xNote, yNote);
	}
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(x + 10, y);
	glVertex2i(x + 10, y - 35);
	glEnd();
	if (selection == 2)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);
	if (selection == 2 || selection == 3) {
		for (int i = 0; i < 64; i++) {
			angle = (double)i * PI / 32.0;
			xNote = x + 30 + cos(angle) * 10;
			yNote = y + sin(angle) * 10;
			glVertex2d(xNote, yNote);
		}
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(x + 40, y);
		glVertex2i(x + 40, y - 35);
		glEnd();
		glBegin(GL_LINES);
		glVertex2i(x + 10, y - 35);
		glVertex2i(x + 40, y - 35);
		glEnd();
	}
}

void Note::move()
{
	x += vx;
	y += vy;
	if (x - 10 <= 0 || x + 10 >= 800 || y + 10 >= 600) {
		x = 340;
		y = 400;
		vx = rand() % 30 - 5;
		vy = rand() % 10 + 2;
	}
}
