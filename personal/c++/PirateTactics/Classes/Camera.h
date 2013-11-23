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
	~Camera();
	
	GLshort getView(GLshort) const;
	void setView(GLshort, GLshort);
	
	static GLshort getZoom();
	void setZoom(GLshort);
	
private:
	Coord2d<GLshort> loc;
	static GLshort zoom;
};

#endif
