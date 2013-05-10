/*
 *  Button.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Button.h"

#include "Color.h"
#include "Image.h"

#include "HitTest.h"


Button::Button(Image* img, const Coord2d<double>& os) : _icon(img, os){	
	//--- GENERAL ---//
	_selected = false;
	_enabled = true;
}


//--- GENERAL ---//
void Button::select(bool s){
	_selected = s;
}

void Button::enable(bool e){
	_enabled = e;
}

bool Button::isEnabled() const{
	return _enabled;
}

const Coord2d<double>& Button::getOffset() const{
	return _icon.getOffset();
}

double Button::getOffset(GLshort c) const{
	return _icon.getOffset(c);
}


GLshort Button::getSize(GLshort c) const{
	return _icon.getSize(c);
}

void Button::setImage(Image* img){
	_icon.setImage(img);
}

Button* Button::getButton(GLshort s){
	return this;
}


//---- DRAW ----//
void Button::draw(bool step){	
	if(_enabled){
		GLfloat currColor[4];
		glGetFloatv(GL_CURRENT_COLOR, currColor);
		if(_selected){
			glColor4f(currColor[R] * 0.5f, currColor[G] * 0.5f, 
						 currColor[B] * 0.5f, currColor[A]);	
		}
		_icon.draw(step);
		glColor4f(currColor[R], currColor[G], currColor[B], currColor[A]);
	}
}


//---- TOUCH ----//
bool Button::isTouching(const Coord2d<GLshort>& p){
	return _enabled && _icon.isTouching(p);
}

void Button::push(GLshort t, const Coord2d<GLshort>& p){
	_selected = isTouching(p);
}

void Button::move(GLshort t, const Coord2d<GLshort>& p){
	_selected = isTouching(p);
}

bool Button::release(GLshort t, const Coord2d<GLshort>& p){
	if(_selected){
		_selected = false;
		return true;
	}
	return false;
}
