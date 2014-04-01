#include "WZ_Geometry.h"

void wz_geometry::drawAxis()
{
	glMatrixMode(GL_MODELVIEW);
	
	// Draw red X vector
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
	glEnd();
		
	// Draw green Y vector
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
	glEnd();

	// Draw blue Z vector
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
	glEnd();
}
void wz_geometry::drawGrid()
{
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1, 1, 1);
	
	// Draw Gridline parallel to x-axis
	for(int i=0; i<50; i++){
		glBegin(GL_LINE_STRIP);
			glVertex3f(-25, 0, i-25);
			glVertex3f(25, 0, i-25);
		glEnd();
	}

	// Draw Gridline parallel to z-axis
	for(int i=0; i<50; i++){
		glBegin(GL_LINE_STRIP);
			glVertex3f(i-25, 0, -25);
			glVertex3f(i-25, 0, 25);
		glEnd();
	}
}

void wz_geometry::renderWireCube( GLdouble dSize )
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /*
     * PWO: I dared to convert the code to use macros...
     */
    glBegin( GL_LINE_LOOP ); N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); glEnd();
    glBegin( GL_LINE_LOOP ); N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); glEnd();

#   undef V
#   undef N
}