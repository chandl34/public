/*
 *  Camera.cpp
 *  When Pirates Attack
 *
 *  Created by Jonathan Chandler on 1/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Camera.h"


Camera::Camera()
{
	_zoom = MAX_ZOOM;
}


//--- GENERAL ---//
GLshort Camera::getRelativeView(GLshort c) const
{
	return _relView[c];
}

GLshort Camera::getView(GLshort c) const
{
	return _view[c];
}

void Camera::setView(GLshort c, GLshort l)
{
	if(l < 0)
		_relView[c] = 0;
	else if(l > CAMERA_BOUND[_zoom][c])
		_relView[c] = CAMERA_BOUND[_zoom][c];
	else
		_relView[c] = l;
	
	_view[c] = _relView[c] * pow(2, MAX_ZOOM - _zoom);
}

GLshort Camera::getZoom() const
{
	return _zoom;
}

void Camera::setZoom(GLshort z)
{		
	double temp = pow(2, _zoom - z);
	_zoom = z;
	
	setView(X, (getRelativeView(X) + 
					(1 - temp) * SCREEN_SIZE[X] / 2) / temp);
	setView(Y, (getRelativeView(Y) + 
					(1 - temp) * (SCREEN_SIZE[Y] - MENU_SIZE[Y]) / 2) / temp);
}

void Camera::centerOn(GLshort x, GLshort y)
{
	setView(X, x / pow(2, MAX_ZOOM - _zoom) - SCREEN_SIZE[X] / 2.0);
	setView(Y, y / pow(2, MAX_ZOOM - _zoom) - (SCREEN_SIZE[Y] - MENU_SIZE[Y]) / 2.0);
}


//---- IO ----//	
void Camera::saveData(ofstream& file)
{
	file << "c " << getZoom() << " " << getRelativeView(X) << " " << getRelativeView(Y) << "\n";
}
