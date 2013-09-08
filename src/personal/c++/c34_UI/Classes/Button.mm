/*
 *  Button.mm
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/25/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Button.h"

Button::Button(Image* image, 
			   const Coord2d<double>& os,
			   const Size2d<GLshort>& size)
: Icon(image, os, size)
{
	_selected = false;
}

Button::~Button()
{
	
}


//--- GENERAL ---//
void Button::select(bool s)
{
	_selected = s;
	_colorMod[R] = -0.2f * s;
	_colorMod[G] = -0.2f * s;
	_colorMod[B] = -0.2f * s;
}


//--- TOUCH ---//
bool Button::push(GLshort t, const Coord2d<GLshort>& p)
{
	bool ret = isTouching(p);
	
	if(ret != _selected)
		select(ret);
	
	return ret;
}

bool Button::move(GLshort t, const Coord2d<GLshort>& p)
{
	return push(t, p);
}

bool Button::release(GLshort t, const Coord2d<GLshort>& p)
{
	if(_selected){
		select(false);
		_eventHandler->handleEvent(_eventID);
		return true;
	}
	
	return false;
}