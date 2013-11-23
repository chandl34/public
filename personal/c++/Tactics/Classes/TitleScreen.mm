/*
 *  TitleScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/30/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "TitleScreen.h"

#include "MainScreen.h"

#include "ImageStorage.h"


TitleScreen::TitleScreen()
: BaseScreen(false)
{
	printf("Building Title Screen...\n");
	_background.setImage(ImageStorage::getBGImage(0));
}

TitleScreen::~TitleScreen()
{
	
}

//---- DRAW ----//
void TitleScreen::draw(bool step)
{
	_background.draw(step);
}

//--- TOUCH ---//
void TitleScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
}

void TitleScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	
}

bool TitleScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	MainScreen::newGame();	
	return true;
}
