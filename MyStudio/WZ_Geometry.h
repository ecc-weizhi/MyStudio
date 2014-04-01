#ifndef _WZ_GEOMETRY
#define _WZ_GEOMETRY

#include "WZ_Math.h"
#include "GL/glut.h"

namespace wz_geometry
{
	void drawAxis();
	void drawGrid();
	void renderWireCube( GLdouble dSize );
};

#endif