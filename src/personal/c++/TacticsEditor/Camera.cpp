/*
 *  Camera.cpp
 *  When Pirates Attack
 *
 *  Created by Jonathan Chandler on 1/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Camera.h"


Camera::Camera(){
	zoom = MAX_ZOOM;
	loc[X] = 0;
	loc[Y] = 0;
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

GLshort Camera::getZoom() const{
	return zoom;
}

void Camera::setZoom(GLshort z){		
	double temp = pow(2, zoom - z);
	zoom = z;
	
	setView(X, (getView(X) + (1 - temp) * MAIN_FRAME_SIZE[X] / 2) / temp);
	setView(Y, (getView(Y) + (1 - temp) * (MAIN_FRAME_SIZE[Y]) / 2) / temp);
}

void Camera::centerOn(GLshort x, GLshort y){
	setView(X, x / pow(2, MAX_ZOOM - zoom) - MAP_VIEW_SIZE[MAX_ZOOM][X] / 2.0);
	setView(Y, y / pow(2, MAX_ZOOM - zoom) - MAP_VIEW_SIZE[MAX_ZOOM][Y] / 2.0);
}