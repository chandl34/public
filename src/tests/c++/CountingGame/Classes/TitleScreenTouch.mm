/*
 *  TitleScreenTouch.mm
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#include "TitleScreen.h"

#include "MainScreen.h"



//--- TOUCH ---//
void TitleScreen::push(GLshort t, const Coord2d<GLshort>& p)
{	
	MainScreen::setScreen(GAME_SCREEN);
}

void TitleScreen::move(GLshort t, const Coord2d<GLshort>& p)
{	
	
}

bool TitleScreen::release(GLshort t, const Coord2d<GLshort>& p)
{	
	return false;
}