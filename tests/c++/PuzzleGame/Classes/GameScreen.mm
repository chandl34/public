/*
 *  GameScreen.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GameScreen.h"

#include "Puzzle.h"

#include "ImageStorage.h"


GameScreen::GameScreen()
: BaseScreen(false)
{
	//bgImage = ImageStorage::getBGImage(0);
	puzzle = new Puzzle(ImageStorage::getBGImage(0), 
							  Size2d<GLshort>(7, 5));
}

GameScreen::~GameScreen()
{
	delete puzzle;
}


//---- DRAW ----//
void GameScreen::draw(bool step)
{
	BaseScreen::draw(step);
	puzzle->draw(step);
}
