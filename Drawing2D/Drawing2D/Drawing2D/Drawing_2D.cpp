#include <iostream>
#include <fstream>
#include <string>
#include "fssimplewindow.h"
#include "Line_2D.h"
#include "Drawing_2D.h"


Drawing2D::Drawing2D() //default constructor
{
}

Drawing2D::~Drawing2D() //destructor
{
	cleanUp();
}

void Drawing2D::readFile(const string ifName)
{
	string currText;
	char *currTextChar;
	ifstream inputFile;
	inputFile.open(ifName); //open file
	//check if it opened
	if (inputFile.is_open()) {
		cleanUp();
		if (!inputFile.eof()) {
			inputFile >> numberOfLines;
		}
		theLines = new Line2D[numberOfLines]; //create dynamic array of Line2D objects
		string garbageString; //needed to store an empty line so that [0] has the first group of values
		getline(inputFile, garbageString);
		for (int i = 0; i < numberOfLines; i++) {
			getline(inputFile, currText);
			currTextChar = new char[currText.size()]; //character array containing the text of 
			strcpy(currTextChar, currText.c_str());   //the line read from the .txt file
			theLines[i].makeFromString(currTextChar);
		}
		inputFile.close();
	}
	else
		cout << "Unable to open file";
}

void Drawing2D::draw() const //draws the array of Line2D objects
{
	for (int i = 0; i < numberOfLines; i++) {
		theLines[i].draw();
	}
}

void Drawing2D::zoom(double locX, double locY, double newScaleFactor, double &scale) const
{   //zooms in and out depending on mouse-wheel rolling input
	double newScale = scale * newScaleFactor;
	for (int i = 0; i < numberOfLines; i++) {
		theLines[i].zoom(locX, locY, newScaleFactor, scale, newScale);
	}
	scale = newScale;
}

void Drawing2D::move(int locX, int locY, int prevLocX, int prevLocY) const
{   //pans if mouse-wheel is pressed and user moves the mouse
	for (int i = 0; i < numberOfLines; i++) {
		theLines[i].move(locX, locY, prevLocX, prevLocY);
	}
}

void Drawing2D::cleanUp()
{   //deallocates memory used for the creation of the dynamic Line2D object array
	numberOfLines = 0; //not necessary
	if (theLines != nullptr)
		delete[] theLines;
	theLines = nullptr;
}
