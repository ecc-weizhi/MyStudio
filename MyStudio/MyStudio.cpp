#include "MyStudio.h"

/** Global Variable
 * ----------------------
 * WND_WIDTH: Width of the window.
 * WND_HEIGHT: Height of the window.
 * prevCursorX: Screen coordinate of the cursor previously.
 * prevCursorY: Screen coordinate of the cursor previously.
 * keyPress: To track keys that are currently pressed.
 **/
int WND_WIDTH = 600;
int WND_HEIGHT = 400;
int prevCursorX;
int prevCursorY;
bool keyPress[128];

WZ_Camera camera;

int main()
{
	// Initializing glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WND_WIDTH, WND_HEIGHT);
	glutCreateWindow("MyStudio");
	glutSetCursor(GLUT_CURSOR_NONE); 
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Registering callback function
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutKeyboardFunc(keyboard_callback);
	glutKeyboardUpFunc(keyboardUp_callback);	
	//glutMouseFunc(mouse);
	glutPassiveMotionFunc(passiveMouse_callback);
	glutTimerFunc(50, checkForMovement_callback, 0);

	// Create our sparkling new camera
	vector3D<float> position = {0, 3, -5};
	vector3D<float> look = {0, 0, 1};
	vector3D<float> up = {0, 1, 0};
	camera = WZ_Camera(position, look, up, 5);
	
	// Setting up perspective camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, WND_WIDTH / WND_HEIGHT, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z, 
		camera.lookAt().x, camera.lookAt().y, camera.lookAt().z, 
		camera.getUpVector().x, camera.getUpVector().y, camera.getUpVector().z);
	
	glutMainLoop();
	return 0;
}

/**
 * Function: display_callback
 * Description: Function to be called whenever we want to redraw the screen.
 **/
void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw our stuff here
	//drawAxis();
	wz_geometry::drawGrid();
	wz_geometry::renderWireCube(1);

	// Update the perspective camera.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z, 
		camera.lookAt().x, camera.lookAt().y, camera.lookAt().z, 
		camera.getUpVector().x, camera.getUpVector().y, camera.getUpVector().z);

	glutSwapBuffers();	
}

/**
 * Function: reshape_callback
 * Description: Function to be called whenever we resize the window. Update window
 * size information.
 **/
void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	WND_WIDTH = w;
	WND_HEIGHT = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, WND_WIDTH / WND_HEIGHT, 0.1, 100);
}

/**
 * Function: passiveMouse_callback
 * Description: Function to be called whenever the cursor is moved. Call the appropriate
 * functions to update the camera orientation.
 **/
void passiveMouse_callback(int x, int y)
{
	// -ve deltaX is turn left, +ve deltaX is turn right
	// -ve deltaY is turn up, +ve deltaY is turn down
	float deltaX = x - prevCursorX;
	float deltaY = y - prevCursorY;
	
	// Divide deltaX and deltaY to slow the rotation amount.
	camera.rotateCamera(0, -deltaY/5.0, -deltaX/5.0);

	// If cursor approaches edge of screen, warp cursor back to middle. Note that
	// we want to reduce the number of cursor warp as each cursor warp will trigger this
	// function again.
	if( x < 10 || x > (WND_WIDTH-10) || y < 10 || y > (WND_HEIGHT-10) )
	{
		prevCursorX = WND_WIDTH / 2;
		prevCursorY = WND_HEIGHT / 2;

		glutWarpPointer(prevCursorX, prevCursorY);
	}
	else
	{
		prevCursorX = x;
		prevCursorY = y;
	}

	glutPostRedisplay();
}

/**
 * Function: keyboard_callback
 * Description: Set corresponding key to true when pressed. 
 **/
void keyboard_callback (unsigned char key, int x, int y){
	keyPress[key] = true;
}

/**
 * Function: keyboardUp_callback
 * Description: Set corresponding key to false when released. 
 **/
void keyboardUp_callback(unsigned char key, int x, int y){
	keyPress[key] = false;
}

/**
 * Function: checkForMovement_callback
 * Description: Function to be called repeatedly. Perform checking of keypressed currently
 * and handle them.
 **/
void checkForMovement_callback(int value){
	if(keyPress['w'] || keyPress['W']){
		camera.moveCamera(0.1, 0, 0);	
		glutPostRedisplay();
	}

	if(keyPress['s'] || keyPress['S']){
		camera.moveCamera(-0.1, 0, 0);	
		glutPostRedisplay();
	}

	if(keyPress['a'] || keyPress['A']){
		camera.moveCamera(0, -0.1, 0);	
		glutPostRedisplay();
	}

	if(keyPress['d'] || keyPress['D']){
		camera.moveCamera(0, 0.1, 0);	
		glutPostRedisplay();
	}

	if(keyPress['t'] || keyPress['T']){
		camera.moveCamera(0, 0, 0.1);	
		glutPostRedisplay();
	}

	if(keyPress['g'] || keyPress['G']){
		camera.moveCamera(0, 0, -0.1);	
		glutPostRedisplay();
	}

	glutTimerFunc(20, checkForMovement_callback, 0);
}