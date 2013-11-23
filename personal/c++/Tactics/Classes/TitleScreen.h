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

#include "ComplexMenu.h"


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
	ComplexMenu _menu;	
};

#endif

