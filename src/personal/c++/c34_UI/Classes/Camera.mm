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
	_scrollable = false;
	_zoom = MAX_ZOOM;
}


//--- GENERAL ---//
// View
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
	if(l < _bound[c][MIN])
		_relView[c] = _bound[c][MIN];
	else if(l > _bound[c][MAX])
		_relView[c] = _bound[c][MAX];
	else
		_relView[c] = l;
	
	_view[c] = _relView[c] * pow(2, MAX_ZOOM - _zoom);
}

void Camera::centerOn(GLshort x, GLshort y)
{
	setView(X, x / pow(2, MAX_ZOOM - _zoom) - SCREEN_SIZE[X] / 2.0);
	setView(Y, y / pow(2, MAX_ZOOM - _zoom) - (SCREEN_SIZE[Y] - MENU_SIZE[Y]) / 2.0);
}

// Bounds
bool Camera::isScrollable() const
{
	return _scrollable;
}

GLshort Camera::getBound(GLshort c, GLshort b) const
{
	return _bound[c][b];
}

void Camera::setBounds(const Coord2d<GLshort>& bx, 
					   const Coord2d<GLshort>& by)
{
	_bound[X] = bx;
	_bound[Y] = by;
	
	_scrollable = false;
	for(GLshort i = 0; i < 2; ++i){
		for(GLshort j = 0; j < 2; ++j){
			if(_bound[i][j] != 0){
				_scrollable = true;
				return;
			}
		}
	}
}


// Zoom
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
