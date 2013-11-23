/*
 *  TitleScreen.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/30/12.
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
	void draw(bool, TexAttr* = NULL);
	
	//--- TOUCH ---//
	bool push(GLshort, const Coord2d<GLshort>&);				
	bool move(GLshort, const Coord2d<GLshort>&);				
	bool release(GLshort, const Coord2d<GLshort>&);			
	
	//--- EVENT ---//
	void handleEvent(int, void* = NULL);
	
private:
	
};

#endif

