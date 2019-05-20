#include <stdio.h>
#include <math.h>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "CameraObject.h"


int main(void)
{
	bool terminate = false;
	CameraObject camera;
	int x, gridSpacing = 20;
	double gridSize = 1000;
	int wid, hei;
	char data[255];

	camera.z = 10.0;
	camera.y = 5.0;
	camera.farZ = 1000.;
	FsOpenWindow(16, 16, 800, 600, 1);

	while (!terminate)
	{
		FsPollDevice();

		FsGetWindowSize(wid, hei);

		int key = FsInkey();
		switch (key)
		{
		case FSKEY_ESC:
			terminate = true;
			break;
		}
		if (0 != FsGetKeyState(FSKEY_LEFT))
			camera.h += YsPi / 180.0;

		if (0 != FsGetKeyState(FSKEY_RIGHT))
			camera.h -= YsPi / 180.0;

		if (0 != FsGetKeyState(FSKEY_UP))
			camera.p += YsPi / 180.0;

		if (0 != FsGetKeyState(FSKEY_DOWN))
			camera.p -= YsPi / 180.0;

		if (0 != FsGetKeyState(FSKEY_F)) {
			double vx, vy, vz;
			camera.GetForwardVector(vx, vy, vz);
			camera.x += vx * 0.5;
			camera.y += vy * 0.5;
			camera.z += vz * 0.5;
		}
		if (0 != FsGetKeyState(FSKEY_B)) {
			double vx, vy, vz;
			camera.GetForwardVector(vx, vy, vz);
			camera.x -= vx * 0.5;
			camera.y -= vy * 0.5;
			camera.z -= vz * 0.5;
		}

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.SetUpCameraProjection();
		camera.SetUpCameraTransformation();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here

		glBegin(GL_LINES);
		for (x = -gridSize; x <= gridSize; x += gridSpacing)
		{
			glColor3ub(0, 0, x % 256);
			glVertex3i(x, 0, -gridSize);
			glVertex3i(x, 0, gridSize);
			glVertex3i(-gridSize, 0, x);
			glVertex3i(gridSize, 0, x);
		}
		glEnd();

		// Set up 2D drawing
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);

		camera.printValues(data);
		//std::cout << data << std::endl;
		glColor3ub(0, 0, 0);
		glRasterPos2i(10, 15);

		YsGlDrawFontBitmap6x10(data);

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;
}

