/*
 *  Section.h
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/24/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SECTION_H_
#define SECTION_H_

#include "Icon.h"

#include "Camera.h"


class Section : public Icon{
public:
	Section(Image* = NULL,
			const Coord2d<double>& = Coord2d<double>(0, 0),
			const Size2d<GLshort>& = Size2d<GLshort>(0, 0),
			bool = false);
	virtual ~Section();
	
	//--- GENERAL ---//
	void addComponent(Component*);
	
	//---- DRAW ----//
	void draw(bool, TexAttr* = NULL);	
	
	//--- TOUCH ---//
	bool push(GLshort, const Coord2d<GLshort>&);
	bool move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	//--- GENERAL ---//
	list<Component*> _comp;
	
	// Scrolling
	Camera _camera;	
	bool _showBar;
	
	//--- TOUCH ---//
	Touchable* _touched;
	Coord2d<GLshort> _startPoint;
	Coord2d<GLshort> _lastPoint;
	bool _drag;
};

#endif

