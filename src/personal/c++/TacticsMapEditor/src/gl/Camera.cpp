#include "Camera.h"

float* Camera::pan;
float* Camera::rotation;
bool Camera::orthogonal;

Camera::Camera(){
	pan = new float[3];
	rotation = new float[3];
	orthogonal = true;
	resetView();
}

Camera::~Camera(){
	delete [] pan;
	delete [] rotation;
}

void Camera::resetView(){
	pan[X] = 0;
	pan[Y] = 0;
	pan[Z] = 0.0f;
	rotation[X] = 35.264f; 
	rotation[Y] = 45.0f; 
	rotation[Z] = 0.0f;
}

void Camera::aerialToggle(){
	if(rotation[X] < 36)
		rotation[X] = 60;
	else
		rotation[X] = 35.264f;
}
