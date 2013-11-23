/*
 *  Screen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Screen.h"



Screen::Screen(bool mt)
: Touchable(mt)
{

}

Screen::~Screen()
{

}


void Screen::resetView()
{	
	resetView(SCREEN_PIXEL[X], SCREEN_PIXEL[Y]);
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



BaseScreen::BaseScreen(bool mt)
: Screen(mt)
{
	bgImage = NULL;
}

BaseScreen::~BaseScreen()
{

}


//---- DRAW ----//
void BaseScreen::draw(bool step)
{
	bgImage.draw(step);
}


//---- TOUCH ----//
bool BaseScreen::isTouching(const Coord2d<GLshort>& p)
{
	return true;
}
