/*
 *  Screen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Screen.h"

#include "Image.h"



Screen::Screen(bool mt)
: Controls(mt)
{
	
}

Screen::~Screen()
{
	
}


void Screen::resetView(GLshort x, GLshort y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();		
	glOrtho(0, x, 
			  0, y, 
			  -1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
}



BaseScreen::BaseScreen(bool mt)
: Screen(mt)
{
	bgImage = NULL;
}

BaseScreen::~BaseScreen()
{
	
}


//---- DRAW ----//
void BaseScreen::draw(bool step){
	if(bgImage != NULL){
		glLoadIdentity();
		bgImage->draw(step);
	}
}


//---- TOUCH ----//
bool BaseScreen::isTouching(const Coord2d<GLshort>& p)
{
	return true;
}



SaveableScreen::SaveableScreen(bool mt)
: BaseScreen(mt)
{
	
}

SaveableScreen::~SaveableScreen()
{
	
}
