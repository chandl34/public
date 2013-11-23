/*
 *  MiniMapScreen.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/27/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MINI_MAP_SCREEN_H_
#define MINI_MAP_SCREEN_H_

#include "Screen.h"

#include "ComplexMenu.h"


class MiniMapScreen : public SubScreen{
public:
	MiniMapScreen();
	
	//-- GENERAL --//
	void open();
	void close();
	
	//---- DRAW ----//
	void draw(bool);
	
	//---- TOUCH ----//
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);
};

#endif



