/*
 *  GameScreenTouch.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#include "GameScreen.h"

#include "MainScreen.h"



//--- TOUCH ---//
void GameScreen::push(GLshort t, const Coord2d<GLshort>& p)
{	
	MainScreen::setScreen(TITLE_SCREEN);
}

void GameScreen::move(GLshort t, const Coord2d<GLshort>& p)
{	
	
}

bool GameScreen::release(GLshort t, const Coord2d<GLshort>& p)
{	
	return false;
}
