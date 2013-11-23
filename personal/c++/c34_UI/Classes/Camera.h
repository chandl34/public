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

// todo: remove usage of constants

class Camera{
public:	
	Camera();
	
	//--- GENERAL ---//
	GLshort getRelativeView(GLshort) const;
	GLshort getView(GLshort) const;
	void setView(GLshort, GLshort);
	void centerOn(GLshort, GLshort);
	
	bool isScrollable() const;
	GLshort getBound(GLshort, GLshort) const;
	void setBounds(const Coord2d<GLshort>&, 
				   const Coord2d<GLshort>&);
	
	GLshort getZoom() const;
	void setZoom(GLshort);
	
private:
	//--- GENERAL ---//
	Coord2d<GLshort> _relView;
	Coord2d<GLshort> _view;
	Coord2d<GLshort> _bound[2];
	bool _scrollable;
	GLshort _zoom;
};

#endif
