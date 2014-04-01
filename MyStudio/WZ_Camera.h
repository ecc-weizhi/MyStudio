#ifndef _WZ_CAMERA
#define _WZ_CAMERA

#include "WZ_Math.h"

class WZ_Camera{
private:
	vector3D<float> cameraPosition;
	vector3D<float> lookVector;			// unit vector
	vector3D<float> upVector;			// unit vector
	vector3D<float> rightVector;		// unit vector
	float focalLength;

public:
	WZ_Camera();
	WZ_Camera(vector3D<float> position, vector3D<float> look, vector3D<float> up,
				float focal_length);
	~WZ_Camera();

	vector3D<float> getCameraPosition();
	vector3D<float> getLookVector();
	vector3D<float> getUpVector();

	void rotateCamera(float rollDegree, float pitchDegree, float yawDegree);
	void moveCamera(float forward, float right, float up);
	vector3D<float> lookAt();
};


#endif