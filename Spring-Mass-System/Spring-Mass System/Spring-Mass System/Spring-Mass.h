/*
 /|
  |
 /|                                       Angelos Mavrogiannis
  |                                       Carnegie Mellon University
 /|
  |                             _______
 /|         /\      /\         |       |
  |____    /  \    /  \    ____|       |
 /|    \  /    \  /    \  /    |       |  Use OpenGl to create a schematic
  |     \/      \/      \/     |_______|  drawing of a spring-mass system.
 /|
  |                                       Add functionality to make it
 /|                                       animate.
  |
 /|
  |
 /|

 */

#pragma once

//transformation of a physical coordinate to a screen coordinate
int getScreenCoords(float x, float y, int &screenX, int &screenY);

//Creation of the wall and the fixture lines on the left side of the screen
int drawWall(void);

//This function uses the previous function, getScreenCoords,
//gets screen coordinates for the vertices of the rectangle(mass) and draws the mass
int drawMass(float L, float h, int screenX, int screenY);

//This function gets the required screen coordinates of the spring spiral points,
//uses Line Strip and draws the spring, following the dimensions
int drawSpring(float L, float h, int screenX, int screenY);