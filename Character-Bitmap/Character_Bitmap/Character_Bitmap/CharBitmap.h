/*
	_	  .      _ _ _   _ _ _ .       _ _ _  _ _.       Angelos Mavrogiannis
   / \    |\  | |	    |      |      |	    ||		     Carnegie Mellon University
  / --\   | \ | |_ _ _  |- - - |      |	    | - -.       Bitmap Editor, (.h file)
 /     \  |  \| |_ _ _| |_ _ _ |_ _ _ |_ _ _| _ _|

*/


#pragma once

using namespace std;

class CharBitmap {
private:
	int width, height; // the size of the bitmap
	int magnifyVal = 20; //parameterize so it's not needed to * or / by 20
	char *pixels; // the values of each of the pixels (stored in a 1D array)
				  // using dynamic memory allocation since user picks the desired bitmap size
public:
	CharBitmap(); //default constructor
	~CharBitmap(); // destructor of class
	void cleanUp(); // used to reset and free up all space used by object
	void create(int, int);
	void setPixel(int, int, unsigned char); // sets the pixel value
	char getPixel(int, int) const; // returns the value/color of the pixel
	void draw() const; // draw the bitmap, magnified (use GL_QUADS) and colors defined in pixels array
	void load(const string); // load a bitmap from a file
	void save(const string) const; // save a bitmap to a file
};
