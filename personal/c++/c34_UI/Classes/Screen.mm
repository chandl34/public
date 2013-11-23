/*
 *  Screen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Screen.h"

#include "Icon.h"


Screen::Screen(bool mt)
: Touchable(mt)
{
	
}

Screen::~Screen()
{
	
}


//-- GENERAL --//
void Screen::resetView(GLshort zoom)
{	
	resetView(VIEW_SIZE[zoom][X], VIEW_SIZE[zoom][Y]);
}

void Screen::resetView(GLshort x, GLshort y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();		
	glOrthof(0, y, 
			 0, x, 
			 -1.0, 1.0);
	glRotatef(-90.0, 0, 0, 1.0);	
	glTranslatef(-x, 0, 0);
	
	glMatrixMode(GL_MODELVIEW);
}


//---- DRAW ----//
void Screen::draw(bool step, TexAttr* ta)
{
	_base.draw(step, ta);
}


//---- TOUCH ----//
bool Screen::isTouching(const Coord2d<GLshort>& p)
{
	return _base.isTouching(p);
}



BaseScreen::BaseScreen(bool mt)
: Screen(mt)
{
	_base.setSize(SCREEN_SIZE[X], SCREEN_SIZE[Y]);	
}

BaseScreen::~BaseScreen()
{
	
}


//---- DRAW ----//
void BaseScreen::drawOther(bool step, TexAttr* ta)
{
	
}



SubScreen::SubScreen(bool mt)
: Screen(mt)
{
	_base.setSize(SUBSCREEN_SIZE[X], SUBSCREEN_SIZE[Y]);
	_base.setOffset((SCREEN_SIZE[X] - SUBSCREEN_SIZE[X]) / 2.0, 
					(SCREEN_SIZE[Y] - SUBSCREEN_SIZE[Y]) / 2.0);
}

SubScreen::~SubScreen()
{
	
}
