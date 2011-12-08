#include "Camera.h"

float* Camera::pan = new float[3];
float* Camera::rotation = new float[3];
int* Camera::scr = new int[2];
bool Camera::orthogonal = true;

Camera::Camera(){
	resetView();
	scr[0] = 0; scr[1] = 0;
}

Camera::~Camera(){
	delete [] pan;
	delete [] rotation;
	delete [] scr;
}

void Camera::resetView(){
	pan[X] = 0.0f; pan[Y] = 0.0f; pan[Z] = -50.0f;
	rotation[X] = 35.264f; rotation[Y] = 45.0f; rotation[Z] = 0.0f;
}

void Camera::aerialToggle(){
	if(rotation[X] < 36)
		rotation[X] = 80;
	else
		rotation[X] = 35.264f;
}

void Camera::scroll(){
	if(scr[X] == SCROLL_LEFT && pan[X] < 37.5f)
		pan[X] += 0.25f;
	else if (scr[X] == SCROLL_RIGHT && pan[X] > -39)
		pan[X] -= 0.25f;
	
	if(scr[Y] == SCROLL_UP && pan[Y] > -17)
		pan[Y] -= 0.25f;
	else if (scr[Y] == SCROLL_DOWN && pan[Y] < 17)
		pan[Y] += 0.25f;
}

