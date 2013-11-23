#include "Camera.h"

float* Camera::pan;
float* Camera::rotation;
int* Camera::scr;
bool Camera::orthogonal;
int* Camera::shift;
int* Camera::shiftCap;
float* Camera::incr;

Camera::Camera(){
	pan = new float[3];
	rotation = new float[3];
	scr = new int[2];
	scr[X] = 0; scr[Y] = 0;
	shift = new int[2];
	shift[X] = 22; shift[Y] = 25;
	shiftCap = new int[2];
	shiftCap[X] = 54; shiftCap[Y] = 51;
	incr = new float[2];
	incr[X] = 1.415f;
	incr[Y] = -0.81675f;
	orthogonal = true;
	resetView();
}

Camera::~Camera(){
	delete [] pan;
	delete [] rotation;
	delete [] scr;
	delete [] shift;
	delete [] incr;
}

void Camera::resetView(){
	//pan[X] = 9.2f; 
	//pan[Y] = -2.05f; 
	pan[X] = 37.5f - shift[X]*incr[X];
	pan[Y] = -20.8352f - shift[Y]*incr[Y];
	pan[Z] = -50.0f;
	rotation[X] = 35.264f; 
	rotation[Y] = 45.0f; 
	rotation[Z] = 0.0f;
}

void Camera::aerialToggle(){
	if(rotation[X] < 36)
		rotation[X] = 80;
	else
		rotation[X] = 35.264f;
}

void Camera::scroll(int d, int i){
	if(i == 0)
		return;	
	if(i == 1){		
		if(shift[d] > 0){
			pan[d] += incr[d];
			shift[d]--;
		}
	}
	else{
		if(shift[d] < shiftCap[d]){
			pan[d] -= incr[d];
			shift[d]++;
		}
	}
}

void Camera::scroll(){
	scroll(X, scr[X]);
	scroll(Y, scr[Y]);
}
