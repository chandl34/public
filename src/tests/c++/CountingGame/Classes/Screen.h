/*
 *  Screen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "Touchable.h"

#include "Icon.h"


class Screen : public Touchable{
public:
	virtual ~Screen();
	
protected:	
	Screen(bool);
	
	void resetView();
	void resetView(GLshort, GLshort);
};


class BaseScreen : public Screen{
public:
	virtual ~BaseScreen();
	
	//---- DRAW ----//
	void draw(bool);
	
	//---- TOUCH ----//
	bool isTouching(const Coord2d<GLshort>&);
	
protected:	
	BaseScreen(bool);
	
	Icon bgImage;
};

#endif
