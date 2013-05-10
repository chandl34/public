/*
 *  Camera.h
 *  When Pirates Attack
 *
 *  Created by Jonathan Chandler on 1/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Include.h"


class Camera{
public:	
	Camera();
	
	//--- GENERAL ---//
	GLshort getRelativeView(GLshort) const;
	GLshort getView(GLshort) const;
	void setView(GLshort, GLshort);
	
	GLshort getZoom() const;
	void setZoom(GLshort);
	
	void centerOn(GLshort, GLshort);
	
	//---- IO ----//	
	void saveData(ofstream&);
	
private:
	//--- GENERAL ---//
	Coord2d<GLshort> _relView;
	Coord2d<GLshort> _view;
	GLshort _zoom;
};

#endif
