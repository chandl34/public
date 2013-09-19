/*
 *  MenuScreen.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/30/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MENU_SCREEN_H_
#define MENU_SCREEN_H_

#include "Screen.h"

#include "ComplexMenu.h"


class MenuScreen : public SubScreen{
public:
	MenuScreen();
	
	//-- GENERAL --//
	void open();
	void close();
	
	//---- DRAW ----//
	void draw(bool);
	
	//---- TOUCH ----//
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);
	
private:	
	ComplexMenu _menu;
};

#endif




