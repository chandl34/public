/*
 *  TacticalScreen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TACTICAL_SCREEN_H_
#define TACTICAL_SCREEN_H_

#include "Screen.h"
#include "LevelMap.h"
#include "PopupMenu.h"

class TacticalScreen : public Screen{
public:
	TacticalScreen();
	~TacticalScreen();
	
	bool push(GLshort, const Coord2d<GLshort>&);				// Defined in TacticalScreenTouch.mm
	void move(GLshort, const Coord2d<GLshort>&);				// Defined in TacticalScreenTouch.mm
	void release(GLshort, const Coord2d<GLshort>&);				// Defined in TacticalScreenTouch.mm
	
	void draw(bool);
	
private:
	LevelMap* levelMap;
	PopupMenu* tacticMenu;	
	Touchable* touched[2];
};

#endif
