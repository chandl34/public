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

#include "HitTest.h"


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



BaseScreen::BaseScreen(bool mt)
: Screen(mt)
{
	
}

BaseScreen::~BaseScreen()
{

}


//---- DRAW ----//
void BaseScreen::drawOther(bool step)
{
	
}


//---- TOUCH ----//
bool BaseScreen::isTouching(const Coord2d<GLshort>& p)
{
	return true;
}



MapScreen::MapScreen(bool mt)
: BaseScreen(mt)
{
	//-- GENERAL --//
	_mode = 0;
	_turnOwner = PLAYER;
	
	//--- TOUCH ---//
	_touchCount = 0;
	_drag = false;	
	_actionDelay = 0.5;
	_timePushed = -1;	
}

MapScreen::~MapScreen()
{
	
}

void MapScreen::selectTarget(Movable* m)
{
	_cursor.setOffset(m);
}



SubScreen::SubScreen(bool mt)
: Screen(mt)
{
	_background.setOffset((SCREEN_SIZE[X] - SUBSCREEN_SIZE[X]) / 2.0, 
								 (SCREEN_SIZE[Y] - SUBSCREEN_SIZE[Y]) / 2.0);
}

SubScreen::~SubScreen()
{
	
}


//---- TOUCH ----//
bool SubScreen::isTouching(const Coord2d<GLshort>& p)
{
	return _background.isTouching(p);
}
