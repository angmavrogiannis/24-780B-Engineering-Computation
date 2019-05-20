//Name: Angelos Mavrogiannis

#include <iostream>
#include <fstream>
#include <string>
#include "fssimplewindow.h"
#include"CharBitmap.h"

using namespace std;

int main()
{
	int w, h, key, mouseEvent, magnifyValue = 20;
	int leftButton, middleButton, rightButton, locX, locY;
	string outputFilename, inputFilename;
	bool terminate = false;

	cout << "Please Insert Bitmap size. [width height]" << endl;
	cin >> w >> h; //get user input for window size

	CharBitmap theBitmap;
	theBitmap.create(w, h);
	FsOpenWindow(16, 16, w * magnifyValue, h * magnifyValue, 1); //open window of desired size

	while (!terminate) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		FsPollDevice();

		//track mouse position
		mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);

		key = FsInkey();

		if (FSKEY_0 <= key && key <= FSKEY_7 && 0 <= locX && locX <= w * magnifyValue
			&& 0 <= locY && locY <= h * magnifyValue) {  //check if 0-7 buttons are pressed
			theBitmap.setPixel(locX, locY, '0' + key - FSKEY_0);
		}
		theBitmap.getPixel(locX, locY);
		theBitmap.draw(); //draw the whole bitmap in each iteration

		switch (key) {
		case FSKEY_ESC: //end if user presses Escape
			terminate = true;
			break;
		case FSKEY_S: //save file if user presses S
			cout << "Please enter the filename: " << endl; //prompt user for filename
			cin >> outputFilename;
			theBitmap.save(outputFilename); //implement saving
			break;
		case FSKEY_L: //load file if user presses L
			cout << "Please enter the filename: " << endl; //prompt user for filename
			cin >> inputFilename;
			theBitmap.load(inputFilename); //implement loading
			break;
		}

		FsSwapBuffers();
		FsSleep(20);
	}

	return 0;
}
