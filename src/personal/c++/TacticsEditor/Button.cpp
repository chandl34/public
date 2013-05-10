/*
 *  Button.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Button.h"

#include "Image.h"

#include "HitTest.h"


Button::Button(Image* img, const Coord2d<double>& os) : icon(img, os){	
	//--- GENERAL ---//
	selected = false;
	enabled = true;
}


//--- GENERAL ---//
void Button::select(bool s){
	selected = s;
}

void Button::enable(bool e){
	enabled = e;
}

bool Button::isEnabled() const{
	return enabled;
}

const Coord2d<double>& Button::getOffset() const{
	return icon.getOffset();
}

double Button::getOffset(GLshort c) const{
	return icon.getOffset(c);
}


GLshort Button::getSize(GLshort c) const{
	return icon.getSize(c);
}

void Button::setImage(Image* img){
	icon.setImage(img);
}

Button* Button::getButton(GLshort s){
	return this;
}


//---- DRAW ----//
void Button::draw(bool step){
	if(!selected && enabled)
		icon.draw(step);
}


//---- TOUCH ----//
bool Button::isTouching(const Coord2d<GLshort>& p){
	return enabled && icon.isTouching(p);
}

void Button::push(GLshort t, const Coord2d<GLshort>& p){
	selected = isTouching(p);
}

void Button::move(GLshort t, const Coord2d<GLshort>& p){
	selected = isTouching(p);
}

bool Button::release(GLshort t, const Coord2d<GLshort>& p){
	if(selected){
		selected = false;
		return true;
	}
	return false;
}
