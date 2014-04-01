#include "WZ_Camera.h"

WZ_Camera::WZ_Camera()
{
	cameraPosition.x = 0;
	cameraPosition.y = 0;
	cameraPosition.z = -10;
	lookVector.x = 0;
	lookVector.y = 0;
	lookVector.z = 1;
	upVector.x = 0;
	upVector.y = 1;
	upVector.z = 0;
	rightVector = normalize(crossProduct(lookVector, upVector));
	focalLength = 10;
}

WZ_Camera::WZ_Camera(vector3D<float> position, vector3D<float> look, vector3D<float> up,
						float focal_length)
{
	cameraPosition = position;
	lookVector = look;
	upVector = up;
	rightVector = normalize(crossProduct(look, up));
	focalLength = focal_length;
}

WZ_Camera::~WZ_Camera()
{
}

vector3D<float> WZ_Camera::getCameraPosition(){ return cameraPosition; }
vector3D<float> WZ_Camera::getLookVector(){ return lookVector; }
vector3D<float> WZ_Camera::getUpVector(){ return upVector; }

/**
 * Function: rotateCamera
 * Description: Rotate this camera by the given 3 angle of rotations with respect
 * to its current orientation. Rotation is done by changing the lookVector, upVector
 * and rightVector of this camera.
 **/
void WZ_Camera::rotateCamera(float rollDegree, float pitchDegree, float yawDegree)
{
	// Calculate transformation matrix
	Matrix4By4<float> rotationMatrix_along_look = makeRotationMatrix(rollDegree, lookVector);
	Matrix4By4<float> rotationMatrix_along_right = makeRotationMatrix(pitchDegree, rightVector);
	Matrix4By4<float> rotationMatrix_along_up = makeRotationMatrix(yawDegree, upVector);
	Matrix4By4<float> rotationMatrix = rotationMatrix_along_look * rotationMatrix_along_right * rotationMatrix_along_up;

	//transform the 3 vertex
	upVector = applyMatrix(rotationMatrix, upVector);
	lookVector = applyMatrix(rotationMatrix, lookVector);
	rightVector = applyMatrix(rotationMatrix, rightVector);
}

/**
 * Function: moveCamera
 * Description: Move this camera by the given amount in the 3 direction of movement 
 * with respect to its current orientation. Rotation is done by changing the position 
 * of this camera.
 **/
void WZ_Camera::moveCamera(float forward, float right, float up)
{
	cameraPosition.x += forward*lookVector.x + right*rightVector.x + up*upVector.x;
	cameraPosition.y += forward*lookVector.y + right*rightVector.y + up*upVector.y;
	cameraPosition.z += forward*lookVector.z + right*rightVector.z + up*upVector.z;
}

/**
 * Function: lookAt
 * Description: Calculate lookAt position vector base on current position
 * and look at direction vector.
 **/
vector3D<float> WZ_Camera::lookAt()
{
	vector3D<float> result;
	result.x = cameraPosition.x + focalLength * lookVector.x;
	result.y = cameraPosition.y + focalLength * lookVector.y;
	result.z = cameraPosition.z + focalLength * lookVector.z;

	return result;
}