/*
 *  Camera.cpp
 *  When Pirates Attack
 *
 *  Created by Jonathan Chandler on 1/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Camera.h"


GLshort Camera::zoom = MAX_ZOOM;


Camera::Camera(){
	
}

Camera::~Camera(){
	
}


GLshort Camera::getView(GLshort c) const{
	return loc[c];
}

void Camera::setView(GLshort c, GLshort l){
	if(l < 0)
		loc[c] = 0;
	else if(l > CAMERA_BOUND[zoom][c])
		loc[c] = CAMERA_BOUND[zoom][c];
	else
		loc[c] = l;
}

GLshort Camera::getZoom(){
	return zoom;
}

void Camera::setZoom(GLshort z){		
	GLfloat temp = pow(2, zoom - z);
	zoom = z;
	setView(X, (getView(X) + (1 - temp)*SCREEN_PIXEL[X]/2)/temp);
	setView(Y, (getView(Y) + (1 - temp)*(SCREEN_PIXEL[Y] - MENU_SIZE[Y])/2)/temp);
}
