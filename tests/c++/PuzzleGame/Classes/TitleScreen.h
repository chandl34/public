/*
 *  TitleScreen.h
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TITLE_SCREEN_H_
#define TITLE_SCREEN_H_

#include "Screen.h"


class TitleScreen : public BaseScreen{
public:
	TitleScreen();
	~TitleScreen();
	
	//---- DRAW ----//
	void draw(bool);
	
	//--- TOUCH ---//
	void push(GLshort, const Coord2d<GLshort>&);		
	void move(GLshort, const Coord2d<GLshort>&);		
	bool release(GLshort, const Coord2d<GLshort>&);		
	
private:
	
};

#endif