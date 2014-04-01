#ifndef _WZ_MATH
#define _WZ_MATH
#define _USE_MATH_DEFINES	// This is to enable us to use macros in math.h (e.g. M_PI)

#include <math.h>
#include "Matrix4By4.h"

// Structure to represent a vector (either direction vector or position vector).
template <class T>
struct vector3D{
	T x, y, z;
};

template <class T>
T distanceBetween(vector3D<T> pt1, vector3D<T> pt2)
{
	T xDiff = pt1.x - pt2.x;
	T yDiff = pt1.y - pt2.y;
	T zDiff = pt1.z - pt2.z;

	return (sqrt(xDiff*xDiff + yDiff*yDiff + zDiff*zDiff));
}

template <class T>
vector3D<T> normalize(vector3D<T> vector)
{
	vector3D<T> origin = {0, 0, 0};
	T dist = distanceBetween(vector, origin);
	vector.x = (vector.x) / dist;
	vector.y = (vector.y) / dist;
	vector.z = (vector.z) / dist;

	return vector;
}

template <class T>
vector3D<T> directionVector(vector3D<T> beginPt, vector3D<T> endPt)
{
	vector3D<T> direction;
	direction.x = endPt.x - beginPt.x;
	direction.y = endPt.y - beginPt.y;
	direction.z = endPt.z - beginPt.z;

	return direction;
}

template <class T>
vector3D<T> crossProduct(vector3D<T> vector1, vector3D<T> vector2)
{
	/**
	 * Given direction vector a and b:
	 * a x b	=	|	i	j	k	|
	 *				|	a1	a2	a3	|
	 *				|	b1	b2	b3	|
	 *
	 *			=	|	a2	a3	|		|	a1	a3	|		|	a1	a2	|
	 *				|	b2	b3	|i   -	|	b1	b3	|j  +	|	b1	b2	|k
	 *
	 * where	|	a	b	|
	 *			|	c	d	| = ad - bc
	 **/

	// Macro to associate a1, a2, ... with vector1.x, vector1.y, ... 
	#define a1 vector1.x
	#define a2 vector1.y
	#define a3 vector1.z
	#define b1 vector2.x
	#define b2 vector2.y
	#define b3 vector2.z

	vector3D<T> result;
	result.x = a2 * b3 - a3 * b2;
	result.y = -( a1 * b3 - a3 * b1 );
	result.z = a1 * b2 - a2 * b1;

	// Undefine macros declare in this function.
	#undef a1
	#undef a2
	#undef a3
	#undef b1
	#undef b2
	#undef b3

	return result;
}

template <class T>
Matrix4By4<T> makeRotationMatrix(float degree, vector3D<T> normalizedAxis)
{
	/**
	 * Given unit vector u = (ux, uy, uz), rotation matrix of angle Theta 
	 * anti clockwise about an axis in the direction of u is:
	 *
	 *		[ cosTheta+(1-cosTheta)ux^2			ux*uy(1-cosTheta)-uz*sinTheta	ux*uz(1-cosTheta)+uy*sinTheta	0	]
	 *	R =	[ uy*ux(1-cosTheta)+uz*sinTheta		cosTheta+(1-cosTheta)uy^2		uy*uz(1-cosTheta)-ux*sinTheta	0	]
	 *		[ uz*ux(1-cosTheta)-uy*sinTheta		uz*uy(1-cosTheta)+ux*sinTheta	cosTheta+(1-cosTheta)uz^2		0	]
	 *		[ 0									0								0								1	]
	 **/


	T ux = normalizedAxis.x;
	T uy = normalizedAxis.y;
	T uz = normalizedAxis.z;
	float cosTheta = cos( toRadian(degree) );
	float sinTheta = sin( toRadian(degree) );
	
	T m0 = cosTheta + ( 1.0 - cosTheta ) * ux * ux;
	T m1 = ux * uy * ( 1.0 - cosTheta ) - uz * sinTheta;
	T m2 = ux * uz * ( 1.0 - cosTheta ) + uy * sinTheta;
	T m3 = 0;

	T m4 = uy * ux * ( 1.0 - cosTheta ) + uz * sinTheta;
	T m5 = cosTheta + ( 1.0 - cosTheta ) * uy * uy;
	T m6 = uy * uz * ( 1.0 - cosTheta ) - ux * sinTheta;
	T m7 = 0;

	T m8 = uz * ux * ( 1.0 - cosTheta ) - uy * sinTheta;
	T m9 = uz * uy * ( 1.0 - cosTheta ) + ux * sinTheta;
	T m10 = cosTheta + ( 1.0 - cosTheta ) * uz * uz;
	T m11 = 0;
	
	T m12 = 0;
	T m13 = 0;
	T m14 = 0;
	T m15 = 1;

	Matrix4By4<T> R = Matrix4By4<T>( m0, m1, m2, m3,
									m4, m5, m6, m7,
									m8, m9, m10, m11,
									m12, m13, m14, m15);

	return R;
}

template <class T>
vector3D<T> applyMatrix(Matrix4By4<T> transformationMatrix, vector3D<T> vector)
{
	/**
	 * Given transformation matrix M and vector V, matrix multiplication of M and V,
	 *			[	m0	m1	m2	m3	]		[ vx ]		[ m0*vx + m1*vy + m2*vz + m3	]
	 * M * V =	[	m4	m5	m6	m7	]	*	[ vy ]  =	[ m4*vx + m5*vy + m6*vz + m7	]
	 *			[	m8	m9	m10	m11 ]		[ vz ]		[ m8*vx + m9*vy + m10*vz + m11	]
	 *			[	0	0	0	1	]		[  1 ]		[ 1								]
	 **/
	
	T m0 = transformationMatrix[0];
	T m1 = transformationMatrix[1];
	T m2 = transformationMatrix[2];
	T m3 = transformationMatrix[3];
	T m4 = transformationMatrix[4];
	T m5 = transformationMatrix[5];
	T m6 = transformationMatrix[6];
	T m7 = transformationMatrix[7];
	T m8 = transformationMatrix[8];
	T m9 = transformationMatrix[9];
	T m10 = transformationMatrix[10];
	T m11 = transformationMatrix[11];

	T vx = vector.x;
	T vy = vector.y;
	T vz = vector.z;

	vector.x = m0*vx + m1*vy + m2*vz + m3;
	vector.y = m4*vx + m5*vy + m6*vz + m7;
	vector.z = m8*vx + m9*vy + m10*vz + m11;

	return vector;
}

float toRadian(float degree);
float toDegree(float radian);

#endif