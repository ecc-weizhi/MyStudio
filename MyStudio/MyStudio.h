#ifndef _MY_STUDIO
#define _MY_STUDIO

#include "WZ_Camera.h"
#include "WZ_Geometry.h"

void display_callback();
void reshape_callback(int w, int h);
void passiveMouse_callback(int x, int y);
void keyboard_callback (unsigned char key, int x, int y);
void keyboardUp_callback(unsigned char key, int x, int y);
void checkForMovement_callback(int value);

#endif