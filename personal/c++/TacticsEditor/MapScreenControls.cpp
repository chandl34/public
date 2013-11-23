/*
 *  MapScreenTouch.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "MapScreen.h"

#include "LevelMap.h"


//--- CONTROLS ---//
void MapScreen::keyDown(GLshort k)
{
	if(levelMap != NULL)	
		levelMap->keyDown(k);
}

void MapScreen::push(GLshort t, const Coord2d<GLshort>& p){		
	if(levelMap != NULL)	
		levelMap->push(t, p);
}

void MapScreen::move(GLshort t, const Coord2d<GLshort>& p){	
	if(levelMap != NULL)			
		levelMap->move(t, p);
}

bool MapScreen::release(GLshort t, const Coord2d<GLshort>& p){	
	if(levelMap != NULL)			
		levelMap->release(t, p);
	return true;
}	
