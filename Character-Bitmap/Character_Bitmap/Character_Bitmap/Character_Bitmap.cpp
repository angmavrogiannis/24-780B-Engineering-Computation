//Name: Angelos Mavrogiannis

#include <iostream>
#include <fstream>
#include "fssimplewindow.h"
#include"CharBitmap.h"

CharBitmap::CharBitmap() //default constructor
{
}

CharBitmap::~CharBitmap() //destructor
{
	cleanUp();
}

void CharBitmap::cleanUp() //resets and frees up space used by the object
{
	width = height = 0;
	if (pixels != nullptr) {
		delete[] pixels;
		pixels = nullptr;
	}
}

void CharBitmap::create(int w, int h)
{
	width = w;
	height = h;
	pixels = new char[width * height]; //create dynamically allocated array of pixels
	for (int c = 0; c < width * height; c++) //set everything to '0' -> black, as a default
		pixels[c] = '0';
}

void CharBitmap::setPixel(int x, int y, unsigned char p)
{
	pixels[y / magnifyVal * width + x / magnifyVal] = p; //assign color value to pixel array ('0'/'1'...)
}

char CharBitmap::getPixel(int x, int y) const //returns character value with the color - code
{

	return pixels[y / magnifyVal * width + x / magnifyVal];
}

void CharBitmap::draw() const
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			switch (pixels[j * width + i]) { //convert key values to actual numbers 0-7
			case '0':
				glColor3ub(0, 0, 0); //black
				break;
			case '1':
				glColor3ub(0, 0, 255); //blue
				break;
			case '2':
				glColor3ub(255, 0, 0); //red
				break;
			case '3':
				glColor3ub(255, 0, 255); //magenta
				break;
			case '4':
				glColor3ub(0, 255, 0); //green
				break;
			case '5':
				glColor3ub(0, 255, 255); //cyan
				break;
			case '6':
				glColor3ub(255, 255, 0); //yellow
				break;
			case '7':
				glColor3ub(255, 255, 255); //white
				break;
			}
			glBegin(GL_QUADS); //draw pixels
			glVertex2i(i * magnifyVal, j * magnifyVal);
			glVertex2i((i + 1) * magnifyVal, j * magnifyVal);
			glVertex2i((i + 1) * magnifyVal, (j + 1) * magnifyVal);
			glVertex2i(i * magnifyVal, (j + 1) * magnifyVal);
			glEnd();
		}
	}
}

void CharBitmap::load(const string ifName)
{	//if file has been created using this program, it can load just typing the filename
	//otherwise, to load a .txt file, the user has to type filename.txt, for example cat.txt
	ifstream inputFile;
	inputFile.open(ifName); //open file
	//check if it opened
	if (inputFile.is_open()) {
		cleanUp();
		if (!inputFile.eof()) {
			inputFile >> width >> height;
			create(width, height);
			for (int i = 0; i < width * height; i++) //read color codes
				inputFile >> pixels[i];
		}
		inputFile.close();
	}
	else
		cout << "Unable to open file";
}

void CharBitmap::save(const string ofName) const
{

	ofstream outputFile;
	outputFile.open(ofName); //open the file
	//check if it opened
	if (outputFile.is_open()) {
		outputFile << width << " " << height << endl;
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				outputFile << pixels[j * width + i]; //write color codes to file
				if (i == width - 1)
					outputFile << endl;
			}
		}
		outputFile.close();
	}
	else
		cout << "Unable to open file";
}
