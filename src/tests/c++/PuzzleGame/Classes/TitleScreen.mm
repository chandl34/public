/*
 *  TitleScreen.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "TitleScreen.h"

#include "ImageStorage.h"


TitleScreen::TitleScreen()
: BaseScreen(false)
{
	bgImage = ImageStorage::getBGImage(0);
}

TitleScreen::~TitleScreen()
{
	
}


//---- DRAW ----//
void TitleScreen::draw(bool step)
{
	BaseScreen::draw(step);
}
