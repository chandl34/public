/*
 *  Button.h
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/25/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Event.h"
#include "Icon.h"


class Button 
: public EventSignaller
, public Icon
{
public:
	Button(Image* = NULL, 
		   const Coord2d<double>& = Coord2d<double>(0, 0),
		   const Size2d<GLshort>& = Size2d<GLshort>(0, 0));
	virtual ~Button();
	
	//--- GENERAL ---//
	void select(bool);
	
	//--- TOUCH ---//
	bool push(GLshort, const Coord2d<GLshort>&);
	bool move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	
private:
	bool _selected;
};

#endif