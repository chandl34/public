/*
 *  Button.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Button.h"
#include "HitTest.h"


Button::Button(Icon* ic){	
	//--- GENERAL ---//
	icon = ic;
	selected = false;
}

Button::~Button(){
	//--- GENERAL ---//
	delete icon;
}


//--- GENERAL ---//
void Button::select(bool s){
	selected = s;
}

bool Button::isSelected() const{
	return selected;
}


//---- DRAW ----//
void Button::draw(bool step){
	if(!selected)
		icon->draw(step);
}


// SCREEN OFFSET //
const Coord2d<GLfloat>& Button::getOffset() const{
	return icon->getOffset();
}

GLfloat Button::getOffset(GLshort c) const{
	return icon->getOffset(c);
}


GLshort Button::getSize(GLshort c) const{
	return icon->getSize(c);
}


//---- TOUCH ----//
bool Button::push(const Coord2d<GLshort>& p){
	return pointInQuad(p, icon->getOffset(), icon->getSize());
}

void Button::move(const Coord2d<GLshort>& p){
	selected = push(p);
}

void Button::release(const Coord2d<GLshort>& p){
	selected = false;
}
