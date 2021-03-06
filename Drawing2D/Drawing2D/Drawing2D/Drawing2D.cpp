/*
   +--------------+
   |.------------.|
   ||            ||
   ||            ||         Angelos Mavrogiannis
   ||            ||         Carnegie Mellon University
   ||            ||         
   |+------------+|
   +-..--------..-+         The Graphics2D class stores display
   .--------------.         parameters for 2D graphics and functions
  / /============\ \        to operate on how the graphics
 / /==============\ \       display is generated.
/____________________\
\____________________/

*/

#include <iostream>
#include <string>
#include "fssimplewindow.h"
#include "Drawing_2D.h"
#include "Line_2D.h"

using namespace std;

void input(string &filename) {
	bool inputOK = false;
	while (!inputOK) {
		cout << "Insert file name: " << endl; //user needs to insert filename.txt !
		cin >> filename;
		if (filename.size() > 255) { //user needs to insert a file name up to 255-characters long
			cout << "Error.Your filename should have maximum 255 characters." << endl;
		}
		else
			inputOK = true;
	}
}

int main()
{
	int leftButton, middleButton, rightButton, locX, locY;
	int key, mouseEvent;
	int prevLocX, prevLocY; //will be used for pan
	double scale = 1.;
	bool terminate = false;
	string filename;
	input(filename);
	Drawing2D theDrawing;
	theDrawing.readFile(filename);
	mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);
	prevLocX = locX; prevLocY = locY;
	FsOpenWindow(16, 16, 800, 600, 1);
	while (!terminate) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		FsPollDevice();
		key = FsInkey();
		mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);
		switch (key) {
		case FSKEY_ESC: //end if user presses Escape
			terminate = true;
			break;
		case FSKEY_WHEELUP: //zoom in
			theDrawing.zoom(locX, locY, 1.1, scale);
			break;
		case FSKEY_WHEELDOWN: //zoom out
			theDrawing.zoom(locX, locY, 1. / 1.1, scale);
			break;
		case FSKEY_SPACE: //reset and cleanUp 
			theDrawing.readFile(filename);
			break;
		}
		if (middleButton) {   // execute pan when middle button is held down
			theDrawing.move(locX, locY, prevLocX, prevLocY);  // essentially, move graphics same amount as the mouse moves
		}
		prevLocX = locX; prevLocY = locY;
		theDrawing.draw();
		FsSwapBuffers();
		FsSleep(10);

	}
	return 0;
}
