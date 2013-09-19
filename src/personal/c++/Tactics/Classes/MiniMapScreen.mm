/*
 *  MiniMapScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/27/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MiniMapScreen.h"

#include "Icon.h"
#include "Image.h"
#include "LevelMap.h"

#include "ImageStorage.h"


MiniMapScreen::MiniMapScreen()
: SubScreen(false)
{	
	printf("Building Mini Map Screen...\n");
	
	Image* img = new Image(Size2d<GLshort>(SUBSCREEN_SIZE[X], 
										   SUBSCREEN_SIZE[Y]), 
						   0);
	ImageStorage::addImage(img);
	_background.setImage(img);
}


//-- GENERAL --//
void MiniMapScreen::open()
{
	
}

void MiniMapScreen::close()
{
	//return _levelMap;
}


//---- DRAW ----//
void MiniMapScreen::draw(bool step)
{
	glColor4f(0.0, 0.0, 0.0, 1.0);
	_background.draw(step);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	LevelMap* levelMap = LevelMap::getInstance();
	levelMap->drawMinimap(step);
}


//---- TOUCH ----//
void MiniMapScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	GLshort x = (p[X] - _background.getOffset(X) - 5) * MINIMAP_MOD;
	GLshort y = (p[Y] - _background.getOffset(Y) - 5) * MINIMAP_MOD;
	
	LevelMap* levelMap = LevelMap::getInstance();
	levelMap->centerView(x, y);
}

void MiniMapScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	push(t, p);
}

bool MiniMapScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	return false;
}
