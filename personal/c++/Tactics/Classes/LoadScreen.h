/*
 *  LoadScreen.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef LOAD_SCREEN_H_
#define LOAD_SCREEN_H_

#include "Screen.h"

#include "ComplexMenu.h"


class LoadScreen : public SubScreen{
public:
	LoadScreen();
	
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



